// this is not my work, i think i found it in a signature on the
// internet.

float R,y=1.5,x,r,A,P,B;int u,h=80,n=80,s;main(c,v)int c;char **v;
{s=(c>1?(h=atoi(v[1])):h)*h/2;for(R=6./h;s%h||(y-=R,x=-2),s;4<(P=B*B)+
(r=A*A)|++u==n&&putchar(*(((--s%h)?(u<n?--u%6:6):7)+"World! \n"))&&
(A=B=P=u=r=0,x+=R/2))A=B*2*A+y,B=P+x-r;}
