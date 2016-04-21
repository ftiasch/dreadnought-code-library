// 注意初始化内存池和 null 节点
struct Node{
	int rev,size; Node *ch[2],*p;
	void set(Node*,int); int dir(); void update(); void relax(); void appRev();
} nodePool[MAX_NODE],*curNode,*null;
Node *newNode(){
	Node *t=curNode++; t->rev=0, t->size=1;
	t->ch[0]=t->ch[1]=t->p=null; return t;
}
struct Splay{
	Node *root;
	Splay(){ root=newNode(); root->set(newNode(),0); root->update(); }
	void rot(Node *t){
		Node *p=t->p; int d=t->dir();
		p->relax(); t->relax();
		if(p==root) root=t;
		p->set(t->ch[!d],d); p->p->set(t,p->dir()); t->set(p,!d);
		p->update();
	}
	void splay(Node *t,Node *f=null){
		for(t->relax();t->p!=f;)
			if(t->p->p==f) rot(t);
			else t->dir()==t->p->dir()?(rot(t->p),rot(t)):(rot(t),rot(t));
		t->update();
	}
};
void initNull(){ curNode=nodePool;null=curNode++;null->size=0; }
void Node::set(Node *t,int _d){ ch[_d]=t; t->p=this; }
int Node::dir(){ return this==p->ch[1]; }
void Node::update(){ size=ch[0]->size+ch[1]->size+1;}
void Node::relax(){ if(rev) ch[0]->appRev(), ch[1]->appRev(), rev=false; }
void Node::appRev(){ if(this==null) return; rev^=true; swap(ch[0],ch[1]); }