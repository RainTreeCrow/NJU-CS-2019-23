#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct Link{
	char name [256];       //文件名
	ino_t     st_ino;     /* inode number */      
	nlink_t   st_nlink;   /* number of hard links */   
	struct Link * next;   //代表指针域，指向直接后继元素
}link;
	
	
	
//初始化	
link * initLink(){
	link * p=(link*)malloc(sizeof(link));//创建一个头结点
	return p;
}
	

//打印链表	
int printElem(link * p){
	link * t=p;
	int i=1;

	//具有相同的inode的文件名连续打印，同时打印出inode
	while (t->next) {
		t=t->next;
		printf("filename=%s,hardlinksnumber=%lu\n",t->name,(unsigned long )t->st_ino);
		i++;
	}
	return -1;
}
	

//插入链表	
link * insertElem(link * p, link *new){
	link * temp=p;//创建临时结点temp
	//首先找到要插入位置的上一个结点
	while (temp!=NULL) {
		if (temp->next == NULL){
		  break;
		}
		if (temp->next->st_ino  >= new->st_ino)  {
		   break;
		}
		temp=temp->next;
	}    

	//向链表中插入结点
	new->next = temp->next;
	temp->next = new;
	return  p;
}


int freecache(link * plist){
	link * p  =  plist; 
	link *q = NULL;
	while (p!= NULL)
	{
		q=p->next;
		free(p);
		p=q;
	}
	plist = NULL; 
	return 0;
}

 
int travel_file(char* path,link * p)
{
    DIR *dir;                   //声明一个文件句柄
    struct dirent *ent;         //存放readdir函数的返回值
    char childpath[256];        //拼凑下一级目录的全路径
 
    dir = opendir(path);
    while((ent = readdir(dir)) != NULL)
    {         //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        if((!strncmp(ent->d_name,".",1)) || (!strncmp(ent->d_name,"..",2)))
            continue;

        if(ent->d_type & DT_DIR)//判断该文件是否是目录
        {                     
            char* format = path[strlen(path)-1] == '/'?"%s%s":"%s/%s";
			struct stat b;	
            snprintf(childpath,256,format,path,ent->d_name);
			int s = stat(childpath, &b);
            	
			//判断硬链接数大于等于2
			if (b.st_nlink >= 2){
				link * newp  = initLink();
				newp->st_ino = b.st_ino;
				newp->st_nlink = b.st_nlink;
				strcpy(newp->name,childpath);
				insertElem(p,newp);
				//printf("[dir]%s%lu\n",childpath,(unsigned long )b.st_nlink);	
			}	
            travel_file(childpath, p);			
        }
        else{
			struct stat b;
		    char* format = path[strlen(path)-1] == '/'?"%s%s":"%s/%s";
			snprintf(childpath,256,format,path,ent->d_name);
			int s = stat(childpath, &b);
			//判断硬链接数大于等于2
			if (b.st_nlink >= 2){	
				link *newp  = initLink();
				newp->st_ino = b.st_ino;
				newp->st_nlink = b.st_nlink;
				strcpy(newp->name,childpath);
				insertElem(p,newp);
				//printf("[file]%s%lu\n",childpath,(unsigned long )b.st_nlink);
			}
            
		}
            
    }
    closedir(dir);              //关闭该文件目录
}
 
//输入需要查看的目录全路径
int main(int argc,char* argv[])
{
	//初始化链表
    link *p=initLink();
	//递归遍历
    travel_file(argv[1], p);
	//遍历打印
	printElem(p);
	//释放内存
	freecache(p);
    return 0;
}



	