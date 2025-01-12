#include"x64.h"
#include<intrin.h>
VOID
DumpCurrentProcessUserPageTable() {
    CR3 Cr3 = { .Value = __readcr3() };
    PA L1ptPa = { 0 };
    L1ptPa.Fields4KB.PPN = Cr3.Fields.PPN;
    DbgPrint("data={title:'Cr3',items:[['Value','0x%016I64X'],['PPN','0x%016I64X'],['L1pt.Pa','0x%016I64X',"
        , Cr3.Value
        , Cr3.Fields.PPN
        , L1ptPa.Value
    );

    PL1PTE L1pt = (PL1PTE)MmGetVirtualForPhysical(L1ptPa.AsLargeInteger);
    DbgPrint("{title:'L1pt',items:[");
    for (int n1 = 0; n1 < 512; n1++)
    {
        if (!L1pt[n1].Fields.P || !L1pt[n1].Fields.U_S) continue;
        PA Pa1 = { 0 };
        Pa1.Fields4KB.PPN = L1pt[n1].Fields.PPN;
        DbgPrint("['%03d', '"
            "  Value=0x%016I64X\\n"
            "    R/W=%I64d\\n"
            "    PPN=0x%016I64X\\n"
            "L2pt.Pa=0x%016I64X',"
            , n1
            , L1pt[n1].Value
            , L1pt[n1].Fields.R_W
            , L1pt[n1].Fields.PPN
            , Pa1.Value
        );
        PL2PTE L2pt = (PL2PTE)MmGetVirtualForPhysical(Pa1.AsLargeInteger);
        DbgPrint("{title:'L1pt[%03d].L2pt',items:[", n1);
        for (int n2 = 0; n2 < 512; n2++)
        {
            if (!L2pt[n2].Fields.P || !L2pt[n2].Fields.U_S) continue;
            if (L2pt[n2].Fields1GB.PS) {
                PA Pa2 = { 0 };
                Pa2.Fields1GB.PPN = L2pt[n2].Fields1GB.PPN;
                DbgPrint("['%03d','"
                    "  Value=0x%016I64X\\n"
                    "    R/W=%I64d\\n"
                    "     PS=%I64d\\n"
                    "    PPN=0x%016I64X\\n"
                    "     Pa=0x%016I64X'],"
                    , n2
                    , L2pt[n2].Value
                    , L2pt[n2].Fields1GB.R_W
                    , L2pt[n2].Fields1GB.PS
                    , L2pt[n2].Fields1GB.PPN
                    , Pa2.Value
                );
                continue;
            }
            PA Pa3 = { 0 };
            Pa3.Fields4KB.PPN = L2pt[n2].Fields.PPN;
            DbgPrint("['%03d','"
                "  Value=0x%016I64X\\n"
                "    R/W=%I64d\\n"
                "     PS=%I64d\\n"
                "    PPN=0x%016I64X\\n"
                "L3pt.Pa=0x%016I64X',"
                , n2
                , L2pt[n2].Value
                , L2pt[n2].Fields.R_W
                , L2pt[n2].Fields.PS
                , L2pt[n2].Fields.PPN
                , Pa3.Value
            );
            PL3PTE L3pt = (PL3PTE)MmGetVirtualForPhysical(Pa3.AsLargeInteger);
            DbgPrint("{title:'L1pt[%03d].L2pt[%03d].L3pt',items:[", n1, n2);
            for (int n3 = 0; n3 < 512; n3++)
            {
                if (!L3pt[n3].Fields.P || !L3pt[n3].Fields.U_S) continue;
                if (L3pt[n3].Fields2MB.PS)
                {
                    PA Pa = { 0 };
                    Pa.Fields2MB.PPN = L3pt[n3].Fields2MB.PPN;
                    DbgPrint("['%03d','"
                        "  Value=0x%016I64X\\n"
                        "    R/W=%I64d\\n"
                        "     PS=%I64d\\n"
                        "    PPN=0x%016I64X\\n"
                        "     Pa=0x%016I64X'],"
                        , n3
                        , L3pt[n3].Value
                        , L3pt[n3].Fields2MB.R_W
                        , L3pt[n3].Fields2MB.PS
                        , L3pt[n3].Fields2MB.PPN
                        , Pa.Value
                    );
                    continue;
                }
                PA Pa4 = { 0 };
                Pa4.Fields4KB.PPN = L3pt[n3].Fields.PPN;
                DbgPrint("['%03d','"
                    "  Value=0x%016I64X\\n"
                    "    R/W=%I64d\\n"
                    "     PS=%I64d\\n"
                    "    PPN=0x%016I64X\\n"
                    "L4pt.Pa=0x%016I64X',"
                    , n3
                    , L3pt[n3].Value
                    , L3pt[n3].Fields.R_W
                    , L3pt[n3].Fields.PS
                    , L3pt[n3].Fields.PPN
                    , Pa4.Value
                );
                PL4PTE L4pt = (PL4PTE)MmGetVirtualForPhysical(Pa4.AsLargeInteger);
                DbgPrint("{title:'L1pt[%03d].L2pt[%03d].L3pt[%03d].L4pt',items:[", n1, n2, n3);
                for (int n4 = 0; n4 < 512; n4++)
                {
                    if (!L4pt[n4].Fields.P || !L4pt[n4].Fields.U_S) continue;
                    PA Pa = { 0 };
                    Pa.Fields4KB.PPN = L4pt[n4].Fields.PPN;
                    DbgPrint("['%03d','"
                        "Value=0x%016I64X\\n"
                        "    R/W=%I64d\\n"
                        "  PPN=0x%016I64X\\n"
                        "   Pa=0x%016I64X'],"
                        , n4
                        , L4pt[n4].Value
                        , L4pt[n4].Fields.R_W
                        , L4pt[n4].Fields.PPN
                        , Pa.Value
                    );
                }
                DbgPrint("]}],");
            }
            DbgPrint("]}],");
        }
        DbgPrint("]}],");
    }
    DbgPrint("]}]]}\n");
}

VOID
DumpUserPageTable(PEPROCESS Process) {
    if (PsGetCurrentProcess() == Process)
    {
        DumpCurrentProcessUserPageTable();
        return;
    }
    KAPC_STATE ApcState;
    KeStackAttachProcess(Process, &ApcState);
    DumpCurrentProcessUserPageTable();
    KeUnstackDetachProcess(&ApcState);
}
