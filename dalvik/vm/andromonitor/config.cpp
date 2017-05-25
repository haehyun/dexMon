#include "config.h"

int
andromonitorConfig(void) {
	FILE *fp;
	char buf[256],*line;
	char path[50]="/data/andromonitor/config.txt";
	int n=0;

	if( (fp = fopen(path,"r"))) {
		while( fgets(buf,256,fp)) {
			if(buf[0] == '#' || buf[0] == '\n')
				continue;
		    line = strtok(buf,"=");
		    //ALOGE("msec | 1 line = %s\n",line);
			n = getVariableNumber(line,strlen(line));
			if((line = strtok(NULL,"\n")) != NULL) {
			//	ALOGE("msec | 2 line = %s\n",line);	
				setVariable(n,line,strlen(line));
			}
				
		}	
		fclose(fp);
	}

	return 0;
}

int
getVariableNumber(char *line,int size) {
	
	
	if(strncmp("packageName",line,size) == 0) {
		return 1;
	}
	else if(strncmp("monitorMode",line,size) == 0) {
		return 2;
	}
	else if(strncmp("threadNumber",line,size) == 0) {
		return 3;
	}
	else if(strncmp("classDescriptor",line,size) == 0) {
		return 4;
	}
	else if(strncmp("methodName",line,size) == 0) {
		return 5;
	}
	else if(strncmp("methodDescriptor",line,size) == 0) {
		return 6;
	}
	else if(strncmp("extractFile",line,size) == 0) {
		return 7;
	}
	else if(strncmp("extractParam",line,size) == 0) {
		return 8;
	}
		else if(strncmp("extractInvokeOnly",line,size) == 0) {
		return 9;
	}
	return 0;
}
int
setVariable(int n, char *line, int size) {
	switch(n) {
		case 1: //packageName
			strncpy(gAndromonitor.packageName,line,size-1);
			//ALOGE("msec|setVariable packageName = %s, length = %d", gAndromonitor.packageName, size-1);
			break;
		case 2: //monitorMode
			gAndromonitor.monitorMode=atoi(line);
			break;
		case 3: //target thread number
			gAndromonitor.threadNumber=atoi(line);
			break;
		case 4: //classDescriptor
			strncpy(gAndromonitor.classDescriptor,line,size-1);
			gAndromonitor.length_CD = size-1;
			//ALOGE("msec|setVariable classDescriptor = %s, length = %d", gAndromonitor.classDescriptor, size-1);
			break;
		case 5: //methodName
			strncpy(gAndromonitor.methodName,line,size-1);
		    gAndromonitor.length_MN = size-1;
		    //ALOGE("msec|setVariable methodName = %s, length = %d", gAndromonitor.methodName, size-1);
			break;
		case 6: //methodDescriptor
			strncpy(gAndromonitor.methodDescriptor,line,size-1);
			gAndromonitor.length_MD = size-1;
			//ALOGE("msec|setVariable methodDescriptor = %s, length = %d", gAndromonitor.methodDescriptor, size-1);
			break;
		case 7: //extractAPIinstructions
			if(strncmp("on",line,2) == 0) {
				gAndromonitor.extractFile = true;
			} else if(strncmp("off",line,2) == 0) {
				gAndromonitor.extractFile = false;
			} else {
				ALOGE("config.txt option error");
			}
			break;
		case 8: //extract parameters
			if(strncmp("on",line,2) == 0) {
				gAndromonitor.extractParam = true;
			} else if(strncmp("off",line,2) == 0) {
				gAndromonitor.extractParam = false;
			} else {
				ALOGE("config.txt option error");
			}
			break;
		case 9: //extract invoke sentence only
			if(strncmp("on",line,2) == 0) {
				gAndromonitor.extractInvokeOnly = true;
			} else if(strncmp("off",line,2) == 0) {
				gAndromonitor.extractInvokeOnly = false;
			} else {
				ALOGE("config.txt option error");
			}
			break;	
		default:
			break;
	}
	return 0;
}

int 
getCurrentPackageName(){
	FILE *fp;
	char path[30];

    sprintf(path, "/proc/%d/cmdline", getpid());
    fp = fopen(path, "r");
    fgets(gAndromonitor.currentPackageName, sizeof(gAndromonitor.currentPackageName)-1,fp);
    fclose(fp);

    return 0;
}

