{==============================================================================}
{ --------------------- Pick & Place custom output ----------------------------}
{------------------------------------------------------------------------------}
{-                                                                            -}
{-  Pick & Place data are exported  components                                -}
{-  Units - mm                                                                -}
{-  Out file - Filename of processed PCB with .csv extension                  -}
{-                                                                            -}
{------------------------------------------------------------------------------}
{- Copyright (C) 2018 深圳市嘉立创科技发展有限公司                            -}
{- 版权所有。                                                                 -}
{- 创建者：WJT                                                                -}
{- 最近修改人：WJT                                                            -}
{- 最近时间： 2018-6-16 11:35                                                 -}
{- 修改说明：                                                                 -}
{- 版本：V0.6.0                                                               -}
{==============================================================================}
{- 脚本下载地址:http://club.szlcsc.com/article/details_10024_1.html           -}
{==============================================================================}   
{..............................................................................}
  function ReplaceSub(str, sub1, sub2: String): String;
    var
    aPos: Integer;
    rslt: String;
  begin
    aPos := Pos(sub1, str);
    rslt := '';
    while (aPos <> 0) do begin
      rslt := rslt + Copy(str, 1, aPos - 1) + sub2;
      Delete(str, 1, (aPos-1) + Length(sub1));
      aPos := Pos(sub1, str);
    end;
    Result := rslt + str;
  end;


Function getAngle(x1, y1, x2, y2 :Double): Double;
var
    len_y,len_x, tan_yx ,Angle        : Double;
begin
    len_y :=  Abs(y1-y2);
    len_x :=  Abs(x1-x2);
    if (len_x=0) and (y1 < y2) then
        Begin
            Result := 90.0;
        end
    else if (len_x=0) and (y1 >= y2) then
        Begin
            Result := 270.0;
        end
    else if (len_y=0) and (x1 >= x2) then
        Begin
            Result := 180;
        end
    else if (len_y=0) and (x1 < x2) then
        Begin
            Result := 0;
        end
    else
        Begin
            tan_yx := (y1-y2)/(x1-x2);
            Angle := (arctan(tan_yx)/3.1415926535)*180;
            if Angle < 0 then
            Begin
                Angle := Angle+360;
            end;
            Result := Angle;
        end;
end;
  
  
{..............................................................................}
Procedure DisplayResultsInMessagePanel(Results : TStringList);
Var
    WSM         : IWorkSpace;
    MM          : IMessagesManager;
    ImageIndex  : Integer;
    F           : Boolean;
    I           : Integer;
Begin
    WSM := GetWorkSpace;
    If WSM = Nil Then Exit;

    // Obtain the Messages Panel interface
    MM := WSM.DM_MessagesManager;
    If MM = Nil Then Exit;

    // Tick Icon for the lines in the Message panel
    ImageIndex := 4;

    // Clear out messages from the Message panel...
    MM.ClearMessages;
    MM.BeginUpdate;

    F := False;
    For I := 0 to Results.Count - 1 Do
    Begin
        MM.AddMessage({MessageClass             } '提示: ' + IntToStr(I),
                      {MessageText              } Results.Strings[I],
                      {MessageSource            } '',
                      {MessageDocument          } '',
                      {MessageCallBackProcess   } '',
                      {MessageCallBackParameters} '',
                      ImageIndex,
                      F);
    End;
    MM.EndUpdate;

    // Display the Messages panel in Altium Designer.
    WSM.DM_ShowMessageView;
End;

Procedure MessagePanelClearMessages();
Var
    WSM         : IWorkSpace;
    MM          : IMessagesManager;
Begin
    WSM := GetWorkSpace;
    If WSM = Nil Then Exit;

    // Obtain the Messages Panel interface
    MM := WSM.DM_MessagesManager;
    If MM = Nil Then Exit;

    // Clear out messages from the Message panel...
    MM.ClearMessages;
    MM.BeginUpdate;
    MM.EndUpdate;

    // Display the Messages panel in Altium Designer.
    WSM.DM_ShowMessageView;
End;
{..............................................................................}


Procedure PickAndPlaceOutput;
var
    Board                          : IPCB_Board; // document board object
    Component                      : IPCB_Component; // component object
    Iterator                       : IPCB_BoardIterator;
    ComponentIterator              : IPCB_GroupIterator;
    Pad                            : IPCB_Pad;

    PnPout                         : TStringList;
    BOMout                         : TstringList;
    BOM_row,BOM_row2               : TstringList;
    DuplicateDesignator            : TstringList;

    ErrorList   : TStringList;


    Count                          : Integer;
    FileName                       : TString;
    FilePath                       : TString;
    Document                       : IServerDocument;
    X, Y, Rotation, C_Layer        : TString;
    PadAngle                  : TString;
    Xpad, Ypad, Npad,DDesig        : TString;
    Xpad2, Ypad2                   : TString;
    Xref, Yref                     : TString;
    centerX,centerY                : Double;
    padX1,padX2,padY1,padY2        : Double;

    pinCout                        : Integer;
    Comment_t,Name_t               : IPCB_Text;
    PadTLayer                      : TLayer;
    PadDifferentLayer              : Boolean;

    
    Comment_text,Description_text  : TString;
    Designator_text,Footprint_text : TString;
    LibRef_text,Pins_text          : TString;
    Quantity_text                  : TString;
    SuppliersPartNumber_text       : TString;
    
    r0,r1                          : TString;


    i,j                            : Integer;

    t_Comment,t_Description        : TString;
    t_Designator, t_Footprint      : TString;
    t_LibRef , t_Pins              : TString;
    Quantity                       : Integer;
    t_SuppliersPartNumber          : TString;

    t_Comment2,t_Description2        : TString;
    t_Designator2, t_Footprint2      : TString;
    t_LibRef2 , t_Pins2              : TString;
    Quantity2                        : Integer;
    t_SuppliersPartNumber2           : TString;
    BOM_ok,Pick_ok                   : Boolean;


Begin
 Board := PCBServer.GetCurrentPCBBoard;
    If Not Assigned(Board) Then  // check of active document
       Begin
          ShowMessage('The Current Document is not a PCB Document.');
       Exit;
    End;


    Iterator := Board.BoardIterator_Create;
    Iterator.AddFilter_ObjectSet(MkSet(eComponentObject));
    Iterator.AddFilter_IPCB_LayerSet(LayerSet.AllLayers);
    Iterator.AddFilter_Method(eProcessAll);

    Count := 0;
    PnPout   := TStringList.Create;
    BOMout   := TStringList.Create;
    ErrorList:= TStringList.Create;

    Component := Iterator.FirstPCBObject;

    PnPout.Add('"Designator","Footprint","Mid X","Mid Y","Ref X","Ref Y","Pad X","Pad Y","Layer","Rotation","Comment"' );
    //PnPout.Add('"Designator","Footprint","Mid X","Mid Y","Pad2 X","Pad2 Y","Pad X","Pad Y","Layer","Rotation","Comment","PadAngle"' );
    //BOMout.Add('"Comment","Description","Designator","Footprint","LibRef","Pins","Quantity","SuppliersPartNumber"' );

    ErrorList.Add('以下信息为嘉立创的脚本检查出来,不是AD自带的功能,出现提示的这些元件,建议仔细检查');
    ErrorList.Add('嘉立创的脚本下载地址:http://club.szlcsc.com/article/details_10024_1.html');


    While (Component <> Nil) Do
    Begin
        ComponentIterator := Component.GroupIterator_Create;
        ComponentIterator.AddFilter_ObjectSet(MkSet(ePadObject));
        Pad := ComponentIterator.FirstPCBObject;

        X := '';
        Y := '';
        Xpad := '';
        Ypad := '';
        Xpad2 := '';
        Ypad2 := '';

        padX1 := 0.0;
        padY1 := 0.0;
        padX2 := 0.0;
        padY2 := 0.0;
        PadAngle := '';

        C_Layer := '';

        centerX := 0;
        centerY := 0;
        pinCout := 0;

        Comment_t :=  Component.Comment;
        Name_t    :=  Component.Name;
        
        Comment_text := trim(Comment_t.Text);               
        Designator_text :=  trim(Name_t.Text);
        
        Description_text :=  trim(Component.SourceDescription);//.SourceDesignator;             
        Footprint_text :=  trim(Component.Pattern);
        LibRef_text :=  trim(Component.SourceLibReference); 
        //Ref xy
        Xref := FormatFloat('0.###',FloatToStr(CoordToMMs(Component.X - Board.XOrigin)))+'mm';
        Yref := FormatFloat('0.###',FloatToStr(CoordToMMs(Component.Y - Board.YOrigin)))+'mm';
        
        //{
         if pos(#9,Description_text) <> 0 then
            begin
                ErrorList.Add('Designatorb包含未知字符,已强制替换为空格.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Description_text := ReplaceSub (Description_text, #9, ' ');
            end;
            
         if pos(#10,Description_text) <> 0 then
            begin
                ErrorList.Add('Designatorb包含未知字符,已强制替换为空格.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Description_text := ReplaceSub (Description_text, #10, ' ');
            end;

         if pos(#13,Description_text) <> 0 then
            begin
                ErrorList.Add('Designatorb包含未知字符,已强制替换为空格.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Description_text := ReplaceSub (Description_text, #13, ' ');
            end;
            
         //空格   
         if pos(#32,Designator_text) <> 0 then
            begin
                ErrorList.Add('Designator包含空格,已强制替换为下划线.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Designator_text := ReplaceSub (Designator_text, ' ', '_');
            end;
		 //减号 
		 //if pos('-',Designator_text) <> 0 then
         //    begin
         //        ErrorList.Add('Designator包含减号,为防止识别为区间,已强制替换为下划线.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
         //        Designator_text := ReplaceSub (Designator_text, '-', '_');
         //    end;
         // "
         if pos('"',Comment_text) <> 0 then
            begin
                ErrorList.Add('Comment包含引号,已强制替换为单引号.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Comment_text := ReplaceSub (Comment_text, '"', '''');
            end;                
         if pos('"',Description_text) <> 0 then
            begin
                ErrorList.Add('Description包含引号,已强制替换为单引号.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Description_text := ReplaceSub (Description_text, '"', '''');
            end;
         if pos('"',Designator_text) <> 0 then
            begin
                ErrorList.Add('Designatorb包含引号,已强制替换为单引号.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Designator_text := ReplaceSub (Designator_text, '"', '''');
            end;                
         if pos('"',Footprint_text) <> 0 then
            begin
                ErrorList.Add('Footprint包含引号,已强制替换为单引号.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                Footprint_text := ReplaceSub (Footprint_text, '"', '''');
            end;
         if pos('"',LibRef_text) <> 0 then
            begin
                ErrorList.Add('LibRef包含引号,已强制替换为单引号.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
                LibRef_text := ReplaceSub (LibRef_text, '"', '''');
            end;                
        //}
        
        



        //pad xy
        PadTLayer := Nil;
        PadDifferentLayer := False;

        While (Pad <> Nil) Do
            Begin

                Npad := Pad.Name;
                If Npad = '1' Then
                   Begin
                        padX1 := FloatToStr(CoordToMMs(Pad.x - Board.XOrigin));
                        padY1 := FloatToStr(CoordToMMs(Pad.Y - Board.YOrigin));
                        Xpad := FormatFloat('0.###',padX1)+'mm';
                        Ypad := FormatFloat('0.###',padY1)+'mm';
                   End
                else if  Npad = '2' Then
                   Begin
                        padX2 :=  FloatToStr(CoordToMMs(Pad.x - Board.XOrigin));
                        padY2 :=  FloatToStr(CoordToMMs(Pad.Y - Board.YOrigin));
                        Xpad2 := FormatFloat('0.###',padX2)+'mm';
                        Ypad2 := FormatFloat('0.###',padY2)+'mm';
                   End;

                centerX :=centerX + CoordToMMs(Pad.x - Board.XOrigin);
                centerY :=centerY + CoordToMMs(Pad.Y - Board.YOrigin);
                pinCout := pinCout+1;

                if(PadTLayer = Nil) then
                    begin
                       PadTLayer := Pad.Layer;
                    end
                else if(PadTLayer <> Pad.Layer) then
                    begin
                        PadDifferentLayer := True;
                end;

                Pad := ComponentIterator.NextPCBObject;
            End;

        //mid x
        If (pinCout >1) and (length(trim(Designator_text)) > 0) Then
        Begin
           If (centerX <> 0)  Then
               begin
               X :=  FormatFloat('0.###',FloatToStr( centerX/pinCout))+'mm';
               End
           else
               begin
               x := '0';
               End;
           If (centerY <> 0) Then
              begin
              Y :=  FormatFloat('0.###',FloatToStr( centerY/pinCout))+'mm';
              End
           else
               begin
               Y := '0';
               End;

          //Rotation
          Rotation := FormatFloat('0.##',FloatToStr(Component.Rotation));
          {
          if(Xpad <> '') and (Ypad <> '') and (Xpad2 <> '') and (Ypad2<>'')then
               Begin
                 PadAngle := FormatFloat('0.##',getAngle(padX1, padY1, padX2,padY2) );
               End;
          }

           //Layer
          if (PadDifferentLayer = False)  then  //Some people are in the wrong position,Preferentially according to the pad
             begin

             case PadTLayer of
                eTopLayer: C_Layer := 'T' ;
                eBottomLayer: C_Layer := 'B' ;
                else
                    begin
                     case Component.Layer of
                        eTopLayer: C_Layer := 'T' ;
                        eBottomLayer: C_Layer := 'B' ;
                        end;
                    end
                end;
             IF (Component.Layer <>  PadTLayer)  and ((PadTLayer = eTopLayer)or (PadTLayer = eBottomLayer))  then
             begin
                 // Makes a string list of connections
                 ErrorList.Add('焊盘层信息可能不正确,已强制使用焊盘层作为元件层.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
             end;

             end
          else
              begin
              case Component.Layer of
                 eTopLayer: C_Layer := 'T' ;
                 eBottomLayer: C_Layer := 'B' ;
                 end;

         end;

          if (C_Layer <> '')then
            begin
             Pins_text :=  IntToStr(pinCout);
            
             PnPout.Add('"'+Designator_text + '","' + Footprint_text + '","'+ X + '","' + Y +'","'+ Xref + '","' + Yref + '","' + Xpad + '","' + Ypad  + '","'+  C_Layer + '","' + Rotation +'","' + Comment_text + '"' );
             //PnPout.Add('"'+Designator_text + '","' + Footprint_text + '","'+ X + '","' + Y +'","'+ Xpad2 + '","' + Ypad2 + '","' + Xpad + '","' + Ypad  + '","'+  C_Layer + '","' + Rotation +'","' + Comment_text  +'","' +PadAngle+ '"' );         
             BOMout.Add('"' + Comment_text  + '"' +#7+ '"' +  Description_text    + '"' +#7+ '"' +   Designator_text   + '"' +#7+ '"' +  Footprint_text  + '"' +#7+ '"' + LibRef_text  + '"' +#7+ '"' + Pins_text   + '"' +#7+ '"' +   '1' + '"' );
             //BOMout.Add('"' + Comment_text  + '","' +  Description_text    + '","' +   Designator_text   + '","' +  Footprint_text  + '","' + LibRef_text  + '","' + Pins_text   + '","' +   '1' + '","' +   '' + '"' );

             Inc(Count);
             end
          else
             begin
             // Makes a string list of connections
             ErrorList.Add('未导出BOM和坐标,可能层信息不对.  Designator:'+ Designator_text+ '    Comment:' +Comment_text + '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
          end;
        end
        else If (pinCout >1) and (length(trim(Designator_text))<= 0 ) then
        begin
             // Makes a string list of connections
             ErrorList.Add('未导出BOM和坐标,Designator 是空的.  Comment:' +Comment_text+ '    Ref X:'+ Xref + '  Ref Y:'+  Yref);

        end
        else If (pinCout <=1) then
        begin
             // Makes a string list of connections
             ErrorList.Add('未导出BOM和坐标,引脚数量少于2个.   Designator:'+ Designator_text +'   引脚数为:'+  IntToStr(pinCout)+  '    Comment:' +Comment_text+ '    Ref X:'+ Xref + '  Ref Y:'+  Yref);
        End;


        Component := Iterator.NextPCBObject;
    End;
    Board.BoardIterator_Destroy(Iterator);

    // Display ErrorList
	MessagePanelClearMessages();
    if   ErrorList.Count > 2 then
    begin
         DisplayResultsInMessagePanel(ErrorList);
    End;
 

    //Format BOM table
    for i := 0 to BOMout.Count-1 do
    begin
        BOM_row   := TStringList.Create;
        BOM_row.Delimiter  :=  #7;
        BOM_row.DelimitedText := BOMout[i];

        if  BOM_row.Count = 7 then
        begin
            t_Comment             := BOM_row[0];
            t_Description         := BOM_row[1];
            t_Designator          := BOM_row[2];
            t_Footprint           := BOM_row[3];
            t_LibRef              := BOM_row[4];
            t_Pins                := BOM_row[5];
            Quantity              := 1;
            //t_SuppliersPartNumber := BOM_row[7];
            r0 :=     t_Comment + t_Description + t_Footprint + t_LibRef + t_Pins;// + t_SuppliersPartNumber;
            
            DuplicateDesignator := TStringList.Create; 
            DuplicateDesignator.add( t_Designator );

            for j := i+1 to BOMout.Count-1 do
            begin
                BOM_row2    := TStringList.Create;
                BOM_row2.Delimiter  :=  #7;
                BOM_row2.DelimitedText := BOMout[j];
                //{
                if  BOM_row2.Count = 7 then
                begin
                    t_Comment2             := BOM_row2[0];
                    t_Description2         := BOM_row2[1];
                    t_Designator2          := BOM_row2[2];
                    t_Footprint2           := BOM_row2[3];
                    t_LibRef2              := BOM_row2[4];
                    t_Pins2                := BOM_row2[5];
                    //t_SuppliersPartNumber2 := BOM_row2[7];

                    r1 := t_Comment2 + t_Description2 + t_Footprint2 + t_LibRef2 + t_Pins2;// + t_SuppliersPartNumber2;
                    //{
                    if r0  = r1 then
                    begin
                        Inc(Quantity);
                        //排除重复的位号
                        if(DuplicateDesignator.IndexOf(t_Designator2) = -1) then
                            begin
                            t_Designator := t_Designator + ',' + t_Designator2;
                            DuplicateDesignator.add(t_Designator2);                         
                            end;
                        

                        BOMout[j] := '';
                    end;
                    //}
                end;
                //}
                BOM_row2.Free;
            end;
            DuplicateDesignator.free;
            
            BOMout[i] := '"' + t_Comment  + '","' +  t_Description    + '","' +   t_Designator   + '","'+#31+ +  t_Footprint  + '","' + t_LibRef  + '","' + t_Pins   + '","' +   IntToStr( Quantity) + '"' ;
            
        end;
        BOM_row.Free;
    end;

    //Delete empty line
    i:=BOMout.Count - 1;
    while(i>0)do
    begin
      if Trim(BOMout[i])='' Then
        BOMout.Delete(i);
      Dec(i);
    end;
    BOMout.Sort;
    BOMout.Insert(0,'"Comment","Description","Designator","Footprint","LibRef","Pins","Quantity"' );
    
    //Pick&Place report
    FilePath := ExtractFilePath(Board.FileName);
    FileName := ChangeFileExt(FilePath+'Pick Place for ' + ExtractFileName(Board.FileName),'.csv'); 
    Pick_ok := false; 
    if IsFileInUse(FileName) = true then
        begin
        showmessage(FileName + #9 + ' 文件正在被其他程序使用.无法继续保存');
        PnPout.Free;
        end
    else
        begin
        PnPout.SaveToFile(FileName);
        PnPout.Free;
        Pick_ok := true;    
        end;    
    
    //BOM report
    FileName := ChangeFileExt(FilePath+'BOM for ' + ExtractFileName(Board.FileName),'.csv');
    BOM_ok := false;
    if IsFileInUse(FileName) = true then
        begin
        showmessage(FileName + #9 + ' 文件正在被其他程序使用.无法继续保存');
        BOMout.Free;
        end
    else
        begin
        BOMout.SaveToFile(FileName);
        BOMout.Free;
        BOM_ok := true;
            
        end;    
    
    //ErrorList
    if   ErrorList.Count > 2 then
    begin
		FileName := ChangeFileExt(FilePath+'导出BOM和坐标检查日志 ' + ExtractFileName(Board.FileName),'.csv');
		BOM_ok := false;
		if IsFileInUse(FileName) = true then
			begin
			showmessage(FileName + #9 + ' 文件正在被其他程序使用.无法继续保存');
			ErrorList.Free;
			end
		else
			begin
			ErrorList.SaveToFile(FileName);
			ErrorList.Free;
			BOM_ok := true;
				
			end; 
    End;

	
	
    if (BOM_ok = true) and (Pick_ok = true) then
        begin
        ShowMessage(IntToStr(Count) + ' 个元件,导出的BOM和坐标存放在:' + #13 + FilePath);   
        end
    else if (BOM_ok = false) and (Pick_ok = true) then
        begin
        ShowMessage(IntToStr(Count) + ' 个元件,只导出了坐标,文件存放在:' + #13 + FilePath);
        end
    else if (BOM_ok = true) and (Pick_ok = false) then
        begin
        ShowMessage(IntToStr(Count) + ' 个元件,只导出了BOM,文件存放在:' + #13 + FilePath);
        end;

End;
{..............................................................................}
function IsFileInUse(fName : string ) : boolean;
var
  HFileRes : HFILE;
begin
  Result := false;
  if not FileExists(fName) then
    exit;
  HFileRes := CreateFile(pchar(fName), GENERIC_READ or GENERIC_WRITE,0, nil, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, 0);
  Result := (HFileRes = INVALID_HANDLE_VALUE);
  if not Result then
    CloseHandle(HFileRes);
end;


