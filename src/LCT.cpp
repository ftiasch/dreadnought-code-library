// 注意初始化 null 节点，单点的 isRoot 初始为 true
struct Node{
	Node *ch[2],*p; int isRoot;
	bool dir(); void set(Node*,bool); void update(); void relax();
} *null;
void rot(Node *t){
	Node *p=t->p; bool d=t->dir();
	p->relax(); t->relax(); p->set(t->ch[!d],d);
	if(p->isRoot) t->p=p->p,swap(p->isRoot,t->isRoot);
	else p->p->set(t,p->dir());
	t->set(p,!d); p->update();
}
void splay(Node *t){
	for(t->relax();!t->isRoot;)
		if(t->p->isRoot) rot(t);
		else t->dir()==t->p->dir() ?(rot(t->p),rot(t)) :(rot(t),rot(t));
	t->update();
}
void access(Node *t){
	for(Node *s=null; t!=null; s=t,t=t->p){
		splay(t);
		t->ch[1]->isRoot=true; s->isRoot=false;
		t->ch[1]=s; t->update();
	}
}
bool Node::dir(){ return this==p->ch[1]; }
void Node::set(Node *t,bool _d){ ch[_d]=t; t->p=this; }
void Node::update(){}
void Node::relax(){ if(this==null) return; }