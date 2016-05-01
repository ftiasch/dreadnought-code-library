// 注意初始化 null 节点，单点的 is_root 初始为 true
struct Node{
	Node *ch[2], *p; 
	int is_root, rev;
	bool dir(); 
	void set(Node*, bool); 
	void update(); 
	void relax(); 
	void app_rev();
} *null;
void rot(Node *t){
	Node *p=t->p; bool d=t->dir();
	p->relax(); t->relax(); p->set(t->ch[!d],d);
	if(p->is_root) t->p=p->p,swap(p->is_root,t->is_root);
	else p->p->set(t,p->dir());
	t->set(p,!d); p->update();
}
void splay(Node *t){
	for(t->relax();!t->is_root;)
		if(t->p->is_root) rot(t);
		else t->dir()==t->p->dir() ?(rot(t->p),rot(t)) :(rot(t),rot(t));
	t->update();
}
void access(Node *t){
	for(Node *s=null; t!=null; s=t,t=t->p){
		splay(t);
		if (t->p == null) { /*TODO*/ }
		t->ch[1]->is_root=true; s->is_root=false;
		t->ch[1]=s; t->update();
	}
}
bool Node::dir(){ return this==p->ch[1]; }
void Node::set(Node *t,bool _d){ ch[_d]=t; t->p=this; }
void Node::update(){ }
void Node::app_rev(){ if (this == null) return; rev ^= true; swap(ch[0], ch[1]); }
void Node::relax() { if(this==null) return; if (rev) { ch[0]->app_rev(); ch[1]->app_rev(); rev = false; } }
void make_root(Node *u) { access(u); splay(u); u->app_rev(); }
