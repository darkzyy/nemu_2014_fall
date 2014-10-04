#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_, *tail, *ftail;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
		bp_pool[i].addr =0;
		bp_pool[i].pre_inc=0;
	}
	ftail =&bp_pool[i];
	ftail->NO=i;
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
	tail = NULL;
}
swaddr_t find_bp(int a){
	assert(head);
	BP *p=head;
	while(a!=1){
		a--;
		if(p->next!=NULL)
			p=p->next;
		else
			printf("error input\n");
	}
	return p->addr;
}
void printb(){
	/*printf("head:\n");
	if(head!=NULL){
		BP *p=head;
		printf("%d	%p	%p %x %x\n",p->NO,p,p->next,p->addr,p->pre_inc);
		while(p->next!=NULL){
			p=p->next;
			printf("%d	%p	%p %x %x\n",p->NO,p,p->next,p->addr,p->pre_inc);
		}
	}
	printf("free:\n");
	if(free_!=NULL){
		BP *p=free_;
		printf("%d	%p	%p %x %x\n",p->NO,p,p->next,p->addr,p->pre_inc);
		while(p!=ftail){
			p=p->next;
			printf("%d	%p	%p %x %x\n",p->NO,p,p->next,p->addr,p->pre_inc);
		}
	}*/
	int i=1;
	if(head==NULL){
		printf("all is wrong \n");
		return;
	}
	BP *p=head;
	printf("%d:		addr:%x		inc:%x\n",i,p->addr,p->pre_inc);
	while(p!=tail){
		p=p->next;
		i++;
		printf("%d:		addr:%x		inc:%x\n",i,p->addr,p->pre_inc);
	}
}

int find_pre_inc(swaddr_t eip){
	if(head->addr==eip)
		return head->pre_inc;
	BP *p=head;
	while(p!= tail){
		p=p->next;
		if(p->addr==eip)
			return p->pre_inc;
	}
	if(head==tail){
		printf("eip error\n");
		return 0;
	}
	printf("unknown error\n");
	return 0;
}

void reno(){
	if(free_==NULL){printf("free_ NULL");}
	else {
		BP *p=free_;
		p->NO--;
		while(p->next!=NULL){
			p=p->next;
			p->NO--;
		}
	}
}
void add_bp(swaddr_t addr,int inc){
	if(free_->next==NULL){
		printf("free_已用尽/n");
		return;	
	};
	if(head==NULL){
		head =free_;
		tail=free_;
	}
	else {
		if(head->addr==addr){
			printf("already exists\n");
			return;
		}
		BP *p=head;
		while(p!=tail){
			p=p->next;
			if(p->addr==addr){
				printf("already exists\n");
				return;
			}
		}

		tail->next =free_;
		tail=tail->next;
	}
	free_=free_->next;
	tail->addr=addr;
	tail->pre_inc=inc;
	tail->next=NULL;
}
void free_bp(int NO){
	if(head==NULL){/*第一个节点空*/
		printf("head NULL");
		return;
	}
	BP *p=head;
	if(p->NO!=NO){
		while(p->next!=NULL){/*p有后继时*/
			if(p->next->NO==NO)
				break;
			p=p->next;
		}
		if(p->next==NULL){/*所删除的NO不存在*/
			printf("bp%d doen't exist\n",NO);
			return ;
		}
		p->next->NO=ftail->NO+1;
		p->next->addr=0;
		p->next->pre_inc=0;
		ftail->next=p->next;
		ftail=ftail->next;
		if (p->next->next!=NULL){
			p->next=p->next->next;
			while(p->next!=NULL){/*重置head中的序号*/
				p=p->next;
				p->NO--;
			}
		}
		else
			p->next=NULL;
		tail=p;
		ftail->next=NULL;
		reno();			/*重置free_断点序号*/
		printf("返回成功\n");
	}
	else{/*第一个结点为NO*/
		p->NO=ftail->NO+1;
		p->addr=0;
		p->pre_inc=0;
		ftail->next=head;
		ftail=ftail->next;
		if(head->next!=NULL){
			head=head->next;
			p=head;
			p->NO--;
			while(p->next!=NULL){/*重置head中的序号*/
				p=p->next;
				p->NO--;
			}
			tail=p;
			ftail->next=NULL;
			reno();
			printf("返回成功(head !=NULL)\n");
		}
		else{
			head->addr=0;
			head->pre_inc=0;
			head=NULL;
			tail=NULL;
			reno();
			printf("返回成功(head =NULL)\n");
		}
	}

}





/* TODO: Implement the function of breakpoint */
