#include "setapp.h"


void readAppList(){
	FILE *fp;
	//int i;
	int index = 0;
    char path[30] = "/data/temp/msec.apps";
    char packageList[1024];
    if((fp = fopen(path, "r")) == NULL)
    	return;
    while(fgets(packageList, sizeof(packageList)-1,fp) != NULL)    {
    	/*  
    		Globals.h
    	    string  appname[10][100] : gInterpPortable.appname 
    	    int appmode[10] : gInterpPortable.appmode
    	*/
    	char* curLine = strtok(packageList, "|");
    	strcpy(gInterpPortable.appname[index],curLine);
    	curLine = strtok(NULL, "|");
    	gInterpPortable.appmode[index] = atoi(curLine);
    	index++;
    }
    fclose(fp);
    //ALOGE("msec|packageList : %s",packageList);
    // for(i = 0 ; i < index ; i++)
    // {
    // 	ALOGE("msec|appname : %s",gInterpPortable.appname[i]);
    // 	ALOGE("msec|appmode : %d",gInterpPortable.appmode[i]);
    // }
}
int setCurrentPackageModeAndName(){
	int mode = 0;
		
	setCurrentPackageName();
	mode = setCurrentPackageMode();

	return mode;
}

int setCurrentPackageMode(){
	int index = 0;
	
	//while(gInterpPortable.appmode[++index] != NULL)
	for( index=0 ; index < MAX_NUM_APPS ; index++){
		if(strcmp(gInterpPortable.appname[index],gInterpPortable.currentPackageName)==0){
			//ALOGE("msec|cmp %s to %s",gInterpPortable.appname[index],gInterpPortable.currentPackageName);
			gInterpPortable.currentPackageMode = gInterpPortable.appmode[index];
			return  gInterpPortable.currentPackageMode;
		}
	}

	return 0;

}

char* setCurrentPackageName(){
	FILE *fp;
	char path[30];

    sprintf(path, "/proc/%d/cmdline", getpid());
    fp = fopen(path, "r");
    fgets(gInterpPortable.currentPackageName, sizeof(gInterpPortable.currentPackageName)-1,fp);
    fclose(fp);

    return gInterpPortable.currentPackageName;
}