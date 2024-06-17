#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct Link {
	char name [256];	// file name
	ino_t st_ino;		// inode number      
	nlink_t st_nlink;	// number of hard links
	struct Link* next;	// pointer to next link
} link;

link* initLink() {
	link* p = (link*)malloc(sizeof(link));	// create head link
	return p;
}

int printElem(link* p) {
	link* t = p;
	while (t->next) {
		t=t->next;
		printf("filename: %s\n hardlinksnumber: %lu\n", t->name, (unsigned long )t->st_ino);
	}
	return -1;
}

link* insertElem(link* p, link* new) {
	link* temp = p;
	while (temp!=NULL) {
		if (temp->next == NULL)
			break;
		if (temp->next->st_ino  >= new->st_ino)
			break;
		temp=temp->next;
	}
	new->next = temp->next;
	temp->next = new;
	return p;
}

int freecache(link* plist) {
	link * p  =  plist; 
	link *q = NULL;
	while (p!= NULL) {
		q=p->next;
		free(p);
		p=q;
	}
	plist = NULL; 
	return 0;
}

int travel_file(char* path, link* p) {
    DIR* dir;				// announce a file handle
    struct dirent* ent;		// store the return values of readdir
    char childpath[256];	// constuct child path
    dir = opendir(path);
    while ((ent = readdir(dir)) != NULL) {
        if((!strncmp(ent->d_name,".",1)) || (!strncmp(ent->d_name,"..",2)))
            continue;		// avoid dead loop
        if(ent->d_type & DT_DIR) {
            char* format = path[strlen(path)-1] == '/'?"%s%s":"%s/%s";
			struct stat b;	
            snprintf(childpath, 256, format, path, ent->d_name);
			int s = stat(childpath, &b);
			if (b.st_nlink >= 2){
				link* newp  = initLink();
				newp->st_ino = b.st_ino;
				newp->st_nlink = b.st_nlink;
				strcpy(newp->name, childpath);
				insertElem(p, newp);
				//printf("[dir]%s%lu\n", childpath, (unsigned long)b.st_nlink);	
			}	
            travel_file(childpath, p);			
        }
        else {
			struct stat b;
		    char* format = path[strlen(path)-1] == '/'?"%s%s":"%s/%s";
			snprintf(childpath, 256, format, path, ent->d_name);
			int s = stat(childpath, &b);
			if (b.st_nlink >= 2) {
				link* newp  = initLink();
				newp->st_ino = b.st_ino;
				newp->st_nlink = b.st_nlink;
				strcpy(newp->name, childpath);
				insertElem(p, newp);
				//printf("[file]%s%lu\n", childpath, (unsigned long)b.st_nlink);
			}
            
		}
            
    }
    closedir(dir);
}

int main(int argc,char* argv[])
{
    link *p=initLink();
    travel_file(argv[1], p);
	printElem(p);
	freecache(p);
    return 0;
}
