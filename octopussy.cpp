

//#pragma once


#include <stdio.h>
//#include <tchar.h>
#include <string>
#include <iostream>
#include <ctime>



#include "vix.h"
#include "vm_basic_types.h"

#define master //add path for the master vm copy 
#define USERNAME "fuzzbox__"
#define PASSWORD "admin"
#define VM_HANDLE_ARRAY_SIZE 32

#define glogfile "c:\\secret"   // Guest log file location
#define  hlogfile "c:\\secret" //Host log file location
using namespace std;

VixError err = VIX_OK;
VixHandle hostHandle = VIX_INVALID_HANDLE;
VixHandle jobHandle = VIX_INVALID_HANDLE;
VixHandle vmHandle = VIX_INVALID_HANDLE;
VixHandle cloneVMHandle = VIX_INVALID_HANDLE;
VixHandle vmHandles[VM_HANDLE_ARRAY_SIZE];


int isLoggedIn = 0;
int vmHandleIndex = 0;
int totalVMCount = 0;
int num_vms_clone;
/*void escape_vm()
{
								exit(EXIT_FAILURE);
}
*/
void vm_err()
{

								if (VIX_OK != err)
								{
													//			cout << "Error:__" << dec << err << "  __Reffrence" << vXerr << endl;

																Vix_ReleaseHandle(jobHandle);
																Vix_ReleaseHandle(vmHandle);
																Vix_ReleaseHandle(cloneVMHandle);
																VixHost_Disconnect(hostHandle);
								}
}



void clone_vm()
{
								jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_WORKSTATION, NULL, 0, NULL, NULL, 0, VIX_INVALID_HANDLE, NULL, NULL);
								err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
								vm_err();
								Vix_ReleaseHandle(jobHandle);


								jobHandle = VixVM_Open(hostHandle, master, NULL, NULL);
								err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
								vm_err();
								printf("Select '1' to create single clone\n");
								printf("Select '2' to create multipe clones, Create copies of 5 virtual machines\n");

								int cl_1;
								printf("Enter:");
								cin >> cl_1;

								if (cl_1 == 1)
								{
																string vm_name;
																printf("Provide VM name\n");
																printf("Enter:");
																cin >> vm_name;

																const char *cstr = vm_name.c_str();
																char vm_str[100];
																strncpy(vm_str, vm_path);
																strcat_s(vm_str, cstr);
																strcat_s(vm_str, ".vmx");

																jobHandle = VixVM_Clone(vmHandle, VIX_INVALID_HANDLE, VIX_CLONETYPE_FULL, vm_str, 0, VIX_INVALID_HANDLE, NULL, NULL);
																err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &cloneVMHandle, VIX_PROPERTY_NONE);
																vm_err();

																if (VIX_SUCCEEDED(err))
																{
																								printf("\n Completed \n");
																}
								}
								else if (cl_1 == 2)
								{
																for (int i = 1; i < 6; ++i)

																{
																								string name = to_string(i);
																								const char *cstr = name.c_str();
																								char vm_str[100];
																								strncpy(vm_str, vm_path);
																								strcat_s(vm_str, cstr);
																								strcat_s(vm_str, ".vmx");

																								jobHandle = VixVM_Clone(vmHandle, VIX_INVALID_HANDLE, VIX_CLONETYPE_FULL, vm_str, 0, VIX_INVALID_HANDLE, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &cloneVMHandle, VIX_PROPERTY_NONE);
																								vm_err();
																								if (VIX_SUCCEEDED(err))
																								{
																																printf("\n %d  cloned \n", i);
																								}
																}
								}
}

void VixDiscoveryProc(VixHandle jobHandle, VixEventType eventType, VixHandle moreEventInfo, void *clientData)
{
								VixHandle openJobHandle;
								VixError err = VIX_OK;
								char *url = NULL;
								int num = 0;
								if (VIX_EVENTTYPE_FIND_ITEM != eventType)
								{
																return;
								}
								err = Vix_GetProperties(moreEventInfo, VIX_PROPERTY_FOUND_ITEM_LOCATION, &url, VIX_PROPERTY_NONE);
								if (VIX_SUCCEEDED(err))
								{
																printf("\n Found virtual machine: %s [%d] \n", url, totalVMCount++ + 1);
								}
								else if (VIX_OK != err) {
																vm_err();
																Vix_FreeBuffer(url);
								}
}




void vmware()//exsi input
{


								printf("Select 's' to start all VM's \n");
								printf("Select 'quit' to shutdown all VM's \n");
								printf("Select individual virtual machines to control\n");
								printf("Example:  '1 eq a - e' \nLooking for active virtual machines: \n");


								jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_WORKSTATION, NULL, 0, NULL, NULL, 0, VIX_INVALID_HANDLE, NULL, NULL);
								err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
								vm_err();
								Vix_ReleaseHandle(jobHandle);


								jobHandle = VixHost_FindItems(hostHandle, VIX_FIND_RUNNING_VMS, VIX_INVALID_HANDLE, -1, VixDiscoveryProc, NULL);
								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
								vm_err();
								Vix_ReleaseHandle(jobHandle);

								printf("\nSelect a VM to control::");
								string input;
								cin >> input;


								if (input == "a"||"b"||"c"||"d"||"e"||"f") //1
								{
																jobHandle = VixVM_Open(hostHandle, vm1, NULL, NULL);
																err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
																vm_err();
																printf("%c",input)

																Vix_ReleaseHandle(jobHandle);
								}
								if (input == "quit")
								{
																printf("Enter no Vm's to quit");
																int int_num_vms;
																cin >> int_num_vms
																for (int i = 1; i < int_num_vms; ++i)

																{
																								string name = to_string(i);
																								const char *cstr = name.c_str();
																								char vm_str[100];
																								strncpy(vm_str, vm_path);
																								strcat_s(vm_str, cstr);
																								strcat_s(vm_str, ".vmx");

																								jobHandle = VixVM_Open(hostHandle, vm_str, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
																								vm_err();

																								jobHandle = VixVM_PowerOff(vmHandle, VIX_VMPOWEROP_NORMAL, NULL, NULL);
																								printf("VM powered off[%d] \n", totalVMCount--);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);

																}
																printf("Virtual Machines switched off\n");
																escape_vm();
								}
								else if (input == "s")
								{
																printf("Enter no Vm's to start");
																for (int i = 1; i < 6; ++i)

																{
																								string name = to_string(i);
																								const char *cstr = name.c_str();
																								char vm_str[100];
																								strncpy(vm_str, vm_path);
																								strcat_s(vm_str, cstr);
																								strcat_s(vm_str, ".vmx");

																								jobHandle = VixVM_Open(hostHandle, vm_str, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
																								vm_err();

																								Vix_ReleaseHandle(jobHandle);
																								jobHandle = VixVM_PowerOff(vmHandle, VIX_VMPOWEROP_NORMAL, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);

																								jobHandle = VixVM_PowerOn(vmHandle, VIX_VMPOWEROP_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
																								printf("VMware Started[%d] \n", totalVMCount++ + 1);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();

																								Vix_ReleaseHandle(jobHandle);


																								jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 300, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();

																								Vix_ReleaseHandle(jobHandle);

																								jobHandle = VixVM_LoginInGuest(vmHandle, USERNAME, PASSWORD, 0, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();
																								isLoggedIn = 1;

																								Vix_ReleaseHandle(jobHandle);

																								jobHandle = VixVM_CopyFileFromGuestToHost(vmHandle, glogfile, hlogfile, 0, VIX_INVALID_HANDLE, NULL, NULL);
																								printf("Copying log file \n");
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();
																								printf("Copying log file completed \n");

																}
																printf("Virtual Machines switched on \n");
																escape_vm();
								}
								else
								{
																exit(EXIT_FAILURE);
								}

								void switch_on(); ///___
								{
																printf("\nEnter '1' to start VM or 0 to shutdown::");

																int i;
																cin >> i;

																if (i == 1)
																{ // if i == 0 powered off
																								jobHandle = VixVM_PowerOn(vmHandle, VIX_VMPOWEROP_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
																								printf("VMware Started \n");
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();

																								Vix_ReleaseHandle(jobHandle);


																								jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 300, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();

																								Vix_ReleaseHandle(jobHandle);

																								jobHandle = VixVM_LoginInGuest(vmHandle, USERNAME, PASSWORD, 0, NULL, NULL);
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();
																								isLoggedIn = 1;

																								Vix_ReleaseHandle(jobHandle);

																								jobHandle = VixVM_CopyFileFromGuestToHost(vmHandle, glogfile, hlogfile, 0, VIX_INVALID_HANDLE, NULL, NULL);
																								printf("Copying log file \n");
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																								vm_err();
																								printf("Copying log file completed \n");
																}

																else if (cin.fail())
																{
																								printf("invalid input \n");
																}
																else if (i > 2)
																{
																								printf("invalid input \n");
																}
																else if (i == 0) {
																								jobHandle = VixVM_PowerOff(vmHandle, VIX_VMPOWEROP_NORMAL, NULL, NULL);
																								printf("VMware Powered off \n");
																								err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																}
																Vix_ReleaseHandle(jobHandle);
								};
								exit(EXIT_FAILURE);
}



void main()
{
								printf("\t\t\t Octopussy VMware Fuzzer Distribution \n\t\t\t   Hydra \n");
								string clone_vm_i;
								int input_main;
								printf("Select 1 to control existing Virtual machines on VMware Workstation. \n");
								printf("Select 2 to clone  Virtual machines on VMware Workstation.\n");
								printf("Select 3 to list active Virtual Machines on local Host.\n");

								printf("Enter:");

								cin >> input_main;
								switch (input_main)
								{

								case 1:
																vmware();
																break;

								case 2:
																printf("Available VMimage to clone %s .\n", vm1);
																printf("Select 'y' to continue \n");
																printf("Enter:");
																cin >> clone_vm_i;

																if (clone_vm_i == "y")
																{
																								clone_vm();
																}
																break;
								case 3:
																jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_WORKSTATION, NULL, 0, NULL, NULL, 0, VIX_INVALID_HANDLE, NULL, NULL);
																err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
																vm_err();
																Vix_ReleaseHandle(jobHandle);

																jobHandle = VixHost_FindItems(hostHandle, VIX_FIND_RUNNING_VMS, VIX_INVALID_HANDLE, -1, VixDiscoveryProc, NULL);
																err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
																vm_err();
																Vix_ReleaseHandle(jobHandle);
																break;
								}
}
