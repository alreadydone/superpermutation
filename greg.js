//	Supermutate.js
//	==============
//
//	by Greg Egan
//
//	Generates superpermutations using a method adapted
//	from "Hamiltonicity of the Cayley Digraph ..." by Aaron Williams.
//
//	This method is described on my web page:
//
//	http://www.gregegan.net/SCIENCE/Superpermutations/Superpermutations.html

//	Constructor for an object that generates superpermutations

function Supermutate(n)
{
	this.n=n;
	this.fn=Supermutate.factorial(n);
	this.available=this.fn;
	this.q=new Array(n);
	this.r=new Array(n);
	this.remap=new Array(n);
	this.c=new Array(n);

	for (var i=0;i<n;i++)
	{
		this.r[i]=n-i;							//	Permutation n n-1 n-2 ... 3 2 1
		this.q[i]=1+(n-i)%n;					//	Permutation 1 n n-1 ....... 3 2
	};
	this.p=Supermutate.successor2(this.q);		//	Permutation n-1 n-2 ... 3 2 n 1
	for (var i=0;i<n;i++)
	{
		this.remap[this.p[i]-1]=i+1;			//	Maps digits of p to 1 2 3 ... n
		this.c[i]=this.p[i];					//	Set current permutation to p
	};
	this.supply=n;
}

//	Get current permutation (either full permutation, or just new digits to append to superpermutation), optionally mapped to start at identity.
//	Then advance to next in sequence.

Supermutate.prototype.get = function (full,mapped,cycle)
{
	if (this.available==0)
	{
		//	We have supplied the whole list. Optionally reset and start again.
		
		if (cycle)
		{
			for (var i=0;i<this.n;i++) this.c[i]=this.p[i];
			this.available=this.fn;
			this.supply=this.n;
		}
		else return [];
	};

	var res = mapped ? this.map(this.c) : this.c.slice();
	if (!full) res = res.slice(-this.supply);

	this.available--;
	if (this.available!=0)
	{
		if (Supermutate.weight2edge(this.c) && !Supermutate.arrayEq(this.c,this.q))
		{
			this.c=Supermutate.successor2(this.c);
			this.supply=2;
		}
		else
		{
			this.c=Supermutate.successor1(this.c);
			this.supply=1;
		};
	};

	return res;
}

//	Factorial

Supermutate.factorial = function(n)
{
	if (n<=1) return 1;
	return n*Supermutate.factorial(n-1);
};

//	Compare array elements

Supermutate.arrayEq = function (a,b)
{
	var eq=true;
	for (var i=0;i<a.length;i++) if (a[i]!=b[i]) {eq=false; break;};
	return eq;
};

//	Permutation from following a weight-1 edge;
//	this is a left-rotation.

Supermutate.successor1 = function(q)
{
	var n=q.length;
	var s=new Array(n);
	for (var i=0;i<n;i++) s[i]=q[(i+1)%n];
	return s;
};

//	Permutation from following a weight-2 edge;
//	this is a left-rotation by two then a swap of the last two entries.

Supermutate.successor2 = function(q)
{
	var n=q.length;
	var s=new Array(n);
	for (var i=0;i<n;i++) s[i]=q[(i+2)%n];
	var tmp=s[n-1];
	s[n-1]=s[n-2];
	s[n-2]=tmp;
	return s;
};

//	Determine whether a permutation is followed by a weight-2 edge

Supermutate.weight2edge = function (p)
{
	var n=p.length;
	var npos=p.indexOf(n);					//	Location of n in the permutation
	if (npos==0) return false;				//	Never weight-2 if n comes first
	var rpos=1+(npos%(n-1));				//	Slot to the right of n, cyclically in block omitting first slot
	return p[rpos] == 1+((p[0]+n-3)%(n-1));	//	Weight-2 edge if right slot has one less than first slot, modulo n-1 with a start of 1
};

//	Map digits so that we start superpermutation at 1 2 3 ... n

Supermutate.prototype.map = function (p)
{
	var m=new Array(this.n);
	for (var i=0;i<this.n;i++)
	{
		m[i]=this.remap[p[i]-1];
	};
	return m;
};
