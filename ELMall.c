// constructing all WAPB functions by the action of the cyclic subgroup <\psi> 
// This code will work upto n = 6
#include <stdio.h>
#include <stdlib.h>

int mp(int *, int, int);
int wt(int, int);

int main()
{	int n, i, j, k, l, w, tot, nbe, nbo, totw, bw;
	int s, t, totnb;
	char *psi, *f, *orbl, *flg;
	int *M, **orbe, *orbo, *spn;
	
	printf("n = ");
	scanf("%d",&n);
						  
	spn = (int *) malloc(n*sizeof(int)); //storing n_i = 2^a_i; w = wt(n) 
	t = 1;	w = 0;
	while(t <= n){
		if(n&t){spn[w] = t;	w++;	}
		t = t << 1;
	}

	tot = 1 << n;
	psi = (char *) malloc(n*sizeof(char)); // permutation
	M = (int *) malloc(n*sizeof(int)); // permutation Matrix; row in intger

	s = 0;	t = 0;
	for(i = 0; i < w; i++){		//constructing psi from n
		t = t + spn[i];
		for(j = s; j < t-1; j++)	psi[j] = j+1;
		psi[t-1] = s;
		s = t;
	}
	for(i = 0; i < n; i++){ //constructing permutation matrix M of psi
		t = 1 << psi[i];
		M[i] = t;
	}
	free(spn);free(psi);
	
	orbe = (int **) malloc(tot*sizeof(int *)); // storing even orbits
	for(i = 0; i < tot; i++)
		orbe[i] = (int *) malloc(n*sizeof(int *));
	orbl = (char *) malloc(tot*sizeof(char)); //storing even orbit lengths
	nbo = 1 << w; //number of odd orbits
	orbo = (int *) malloc(nbo*sizeof(int *)); // storing odd orbits
	flg = (char *) malloc(tot*sizeof(char)); // flagging the vectors while creating the orbits 
	for(i = 0; i < tot; i++) flg[i] = 0;
	
	nbe = 0; // number of even orbits
	nbo = 0; // number of odd orbits
	for(i = 0; i < tot; i++){
		if(flg[i] == 0){
			t = mp(M,i,n); //t = psi(i)
			if(t == i){ 
				orbo[nbo++] = i;
				flg[i] = 1;
			}
			else{	l = 0;
				orbe[nbe][l++] = i;
				flg[i] = 1;
				while(t != i){
					orbe[nbe][l++] = t;
					flg[t] = 1;
					t = mp(M,t,n);
				}	
				orbl[nbe] = l;
				nbe++;
			}
		}
	}
	free(flg);free(M);
	
	f = (char *) malloc(tot*sizeof(char)); //storing TT of each function
//	totnb = 1 << 20;  //to reduce search space if one goes n > 6
	totnb = 1 << nbe;
	bw = nbo >> 1;  //half of odd orbits for balanceness
	totw = 1 << nbo; 
	for(k = 0; k < totw; k++){
		if(wt(k,nbo) == bw){ //if k is balanced assign f the bits of k at odd orbits
		t = 1;
		for(i = 0; i < nbo; i++){ //assigning value to f at odd orbit
			if(k&t)	f[orbo[i]] = 1;
			else	f[orbo[i]] = 0;
			t = t << 1;
		}

		for(s = 0; s < totnb; s++){ //to assign the bit value to the 1st vector in every even orbits
			t = 1;
			for(i = 0; i < nbe; i++){
				if((s&t) == 0)
					f[orbe[i][0]] = 0;
				else
					f[orbe[i][0]] = 1;
				t = t << 1;
				l = orbl[i];
				for(j = 1; j < l; j++) f[orbe[i][j]] = f[orbe[i][j-1]]^1;
			}
			//Printing truth table of functions
			for(i = 0; i < tot; i++)	printf("%d",f[i]);
			printf("\n");
		}}
	}
	return(0);
}
int mp(int *M, int v, int n){
	int i, w, t, t2;
	w = 0;	t2 = 1;
	for(i = 0; i < n; i++){
		t = M[i] & v;
		if(t != 0)	w = w ^ t2;
		t2 = t2 << 1;
	}
	return(w);
}
int wt(int v, int n)
{	int i, val = 0, t = 1;
	for (i = 0; i < n; i++)
	{	if (v & t)	val++;
		t = t << 1;
	}
	return val;
}
