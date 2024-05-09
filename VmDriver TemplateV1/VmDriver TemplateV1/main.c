#include<ntifs.h>
#include<intrin.h>
#include"win10.h"
#include"x64.h"
#include <ntddk.h>

VOID
DriverUnload(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	DbgPrint("ÔÙ¼û£¡ %wZ\n", &DriverObject->DriverName);
}

NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);

	DbgPrint("»¶Ó­Äã£¡ %wZ\n", &DriverObject->DriverName);
	DriverObject->DriverUnload = DriverUnload;

	PEPROCESS Process;
	NTSTATUS Status = LookUpProcessByImageName(L"Project2.exe", &Process);
	if (!NT_SUCCESS(Status)) return Status;
	DumpUserPageTable(Process);
	ObDereferenceObject(Process);
    return STATUS_SUCCESS;
}
