//
// Created by draw on 19-5-6.
//

#include "DtFs.h"
#include "DtFile.h"
#include "TextTools.h"
#include "Usart.h"

void DtFs::Load()
{

}

void DtFs::Read(u32 addr)
{

}

void DtFs::Erase(u32 addr)
{

}

void DtFs::Write(u32 addr)
{

}

bl DtFs::Check(void)
{
    DtFsInfo *Info = (DtFsInfo *) Buff;
    Read(0);
    if (Info->Flag != 0x77617244)
    {
        return False;
    }
    Tt.HexCpy(Buff, (u8 *) (&FInfo), sizeof(DtFsInfo));
    return True;
}

void DtFs::Format(u32 sz, u32 fn)
{
    DtFsInfo *Info = (DtFsInfo *) Buff;
    Info->Name[0] = 'X';
    Info->Name[1] = 'C';
    Info->Name[2] = 'F';
    Info->Name[3] = '2';
    Info->Name[4] = '0';
    Info->Name[5] = '1';
    Info->Name[6] = '5';
    Info->Name[7] = '\0';
    Info->FileNbr = fn;
    Info->FileSize = (sz - 11) / fn;

    Info->Flag = 0x77617244;

    Tt.HexCpy(Buff, (u8 *) (&FInfo), sizeof(DtFsInfo));

    Write(0);
    DtFile *f;
    for (int k = 0; k < 10; k++)
    {
        f = (DtFile *) Buff;
        for (int c = 0; c < 16; c++)
        {
            f->Id = (k<<4)+c;
            f->Addr = (f->Id) * (FInfo.FileSize) + 11;
            f->Used = 0;
            f->Len = 0;
            f->Type = 0;
            f++;
        }
        Write(k+1);
    }
}

bl DtFs::Index(DtFile *f, u8 i)
{
    if (i >= FInfo.FileNbr)
    {
        return False;
    }
    Read((i >> 4) + 1);
    Tt.HexCpy(((i - ((i >> 4) << 4)) << 5) + Buff, (u8 *) f, 32);
    return True;
}


