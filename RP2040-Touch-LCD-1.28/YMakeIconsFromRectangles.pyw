v=print
k='BLACK'
j=list
h=len
b='fill'
a=int
Y=max
W='text'
V=min
S='fontSize'
O='ogCords'
M=False
L='type'
K='thickness'
J=True
I='color'
H=None
F='group'
C='rect'
import pygame as A,sys,subprocess as w,os,easygui as x,cv2
from PIL import Image as n,ImageDraw
import numpy as AA
A.init()
l,m=240,240
y=60
z=8
N=A.display.set_mode((l,m))
A.display.set_caption('Icon Creator')
D=[]
B=H
o=0
p=0
q=0
r=0
P=M
T=0
Q=''
c=A.Rect(10,10,220,30)
X=M
def A0(event):
	B=event;global Q,X
	if B.type==A.MOUSEBUTTONDOWN:
		if c.collidepoint(B.pos):X=not X
		else:X=M
	if B.type==A.KEYDOWN:
		if X:
			if B.key==A.K_RETURN:X=M;return Q
			elif B.key==A.K_BACKSPACE:Q=Q[:-1]
			else:Q+=B.unicode
def A1():
	global Q;A.draw.rect(N,(0,0,0),c);B=A.font.Font(H,24)
	try:C=B.render(Q,J,(255,255,255))
	except:Q='';return
	N.blit(C,(c.x+5,c.y+5));A.draw.rect(N,(255,255,255),c,2)
R={(255,255,255):'WHITE',(0,0,0):k,(0,0,255):'BLUE',(255,0,255):'BRED',(255,255,0):'GRED',(0,255,255):'GBLUE',(255,0,0):'RED',(254,0,254):'MAGENTA',(255,190,255):'PINK',(0,255,0):'GREEN',(123,255,255):'CYAN',(254,254,0):'YELLOW',(255,239,82):'GOOD_YELLOW',(189,138,0):'BROWN',(255,130,58):'BRRED',(132,134,132):'GRAY',(58,57,58):'DARKGRAY',(189,186,189):'LIGHT_GRAY',(255,142,0):'ORANGE'}
Z=[8,12,16,20,24]
def A2():
	for E in D:
		if E[L]==W:D.remove(E);D.append(E)
	for B in D:
		if B[L]==C:
			if B[K]==1:A.draw.rect(N,B[I],B[C])
			else:A.draw.rect(N,B[I],B[C],B[K])
		else:
			O=Z[B[S]];P=A.font.Font(H,a(O*1.5));F=P.render(B[W],M,B[I]);G=A.Surface((F.get_size()[0]+11,F.get_size()[1]))
			for J in D:
				if J[L]==C and J[C].collidepoint(B[C].topleft):G.fill(J[I])
			G.blit(F,(11,0));N.blit(G,(B[C].x,B[C].y))
def A3():
	U='Icon.code';global P
	with open(U,'w')as M:
		for A in D:
			F,G,V,X=A[C]
			if A[L]==C:
				N=k
				for(B,E)in R.items():
					if A[I]==B:N=E;break
				if A[K]==1:O='DRAW_FILL_FULL'
				else:O='DRAW_FILL_EMPTY'
				M.write(f"Paint_DrawRectangle({F}, {G}, {F+V}, {G+X}, {N}, DOT_PIXEL_{A[K]}X{A[K]}, {O});\n")
			else:
				Y=A[W];Q=k
				for H in D:
					if H[L]==C and H[C].collidepoint(A[C].topleft):
						for(B,E)in R.items():
							if H[I]==B:Q=E
				T=k
				for(B,E)in R.items():
					if A[I]==B:T=E;break
				a=Z[A[S]];M.write(f'Paint_DrawString_EN({F}, {G}, "{Y}", &Font{a}, {Q}, {T});\n')
		if not P:w.Popen(['notepad.exe',U]);P=J
def A4(img_path):
	global D;P=n.open(img_path);Q,R=P.size;U=240;W=V(U/Q,U/R);X=a(Q*W);Y=a(R*W);P=P.resize((X,Y),resample=n.LANCZOS);T=h(D);M=1;Q,R=P.size;N=P.load();S=0;E=0;H=0;G=0;B=-1
	while H<R:
		while E<Q:
			if(N[E,H][0]+N[E,H][1]+N[E,H][2])/3<100:
				try:
					if N[E,H][3]==255:
						G+=M
						if B==-1:B=E
				except:
					G+=M
					if B==-1:B=E
			elif G>2:D.append({C:A.Rect(B,H,G,M),I:(0,0,0),K:1,b:J,F:T,O:A.Rect(0,0,0,0),L:C});S+=1;G=0;B=-1
			else:G=0;B=-1
			E+=M
		if G>2:D.append({C:A.Rect(B,H,G,M),I:(0,0,0),K:1,b:J,F:T,O:A.Rect(0,0,0,0),L:C});S+=1;G=0;B=-1
		else:G=0;B=-1
		H+=M;E=0;B=-1
	E=0;H=0;G=0;B=-1
	while H<R:
		while E<Q:
			if(N[E,H][0]+N[E,H][1]+N[E,H][2])/3<135 and(N[E,H][0]+N[E,H][1]+N[E,H][2])/3>=100:
				try:
					if N[E,H][3]==255:
						G+=M
						if B==-1:B=E
				except:
					G+=M
					if B==-1:B=E
			elif G>2:D.append({C:A.Rect(B,H,G,M),I:(58,57,58),K:1,b:J,F:T,O:A.Rect(0,0,0,0),L:C});S+=1;G=0;B=-1
			else:G=0;B=-1
			E+=M
		if G>2:D.append({C:A.Rect(B,H,G,M),I:(58,57,58),K:1,b:J,F:T,O:A.Rect(0,0,0,0),L:C});S+=1;G=0;B=-1
		else:G=0;B=-1
		H+=M;E=0;B=-1
	v('Number of Rectangles:',S)
A5=A.time.Clock()
s=J
A6=V(l,m)//2
A7=l//2,m//2
i=M
while s:
	N.fill((20,20,20));A2()
	for E in A.event.get():
		if i:
			t=A0(E)
			if t!=H:i=M;u=t;d=Z[4];e=A.font.Font(H,a(d*1.5));U=e.render(u,J,(0,0,0));A8={C:A.Rect(120,120,U.get_size()[0]+11,U.get_size()[1]),I:(255,255,255),K:1,b:J,F:H,O:A.Rect(0,0,0,0),W:u,S:4,L:W};D.append(A8)
		if E.type==A.QUIT:s=M
		elif E.type==A.MOUSEBUTTONDOWN:
			if E.button==1:
				P=M
				for G in reversed(D):
					if G[C].collidepoint(E.pos):
						B=G;o=E.pos[0]-G[C].x;p=E.pos[1]-G[C].y
						if B[F]!=H:
							q=E.pos[0];r=E.pos[1]
							for f in D:
								if f[F]==B[F]:f[O].x=f[C].x;f[O].y=f[C].y
						D.remove(G);D.append(G);break
			elif E.button==4:
				P=M
				if B:
					if A.key.get_mods()&A.KMOD_SHIFT:
						T=(T+1)%h(R)
						if B[F]!=H:
							for G in D:
								if G[F]==B[F]:G[I]=j(R)[T]
						else:B[I]=j(R)[T]
					elif B[L]==C:
						if B[F]==H:
							if B[K]<z:B[K]+=1
					elif B[S]<h(Z)-1:B[S]+=1;d=Z[B[S]];e=A.font.Font(H,a(d*1.5));U=e.render(B[W],J,(0,0,0));B[C].w=U.get_size()[0];B[C].h=U.get_size()[1]
			elif E.button==5:
				P=M
				if B:
					if A.key.get_mods()&A.KMOD_SHIFT:
						T=(T-1)%h(R)
						if B[F]!=H:
							for G in D:
								if G[F]==B[F]:G[I]=j(R)[T]
						else:B[I]=j(R)[T]
					elif B[L]==C:
						if B[F]==H:B[K]=Y(1,B[K]-1)
					elif B[S]>0:B[S]-=1;d=Z[B[S]];e=A.font.Font(H,a(d*1.5));U=e.render(B[W],J,(0,0,0));B[C].w=U.get_size()[0]+11;B[C].h=U.get_size()[1]
		elif E.type==A.MOUSEBUTTONUP:
			if E.button==1:B=H
		elif E.type==A.MOUSEMOTION:
			P=M
			if B:
				if A.key.get_mods()&A.KMOD_CTRL and A.key.get_mods()&A.KMOD_SHIFT:
					if B[F]==H and B[L]!=W:B[C].width=Y(0,V(E.pos[0],240)-B[C].x);B[C].height=Y(0,V(E.pos[1],240)-B[C].y)
				elif not A.key.get_mods()&A.KMOD_SHIFT:
					if B[F]!=H:
						for G in D:
							if G[F]==B[F]:G[C].x=Y(0,V(E.pos[0]-(q-G[O].x),240-B[C].width));G[C].y=Y(0,V(E.pos[1]-(r-G[O].y),240-B[C].height))
					else:B[C].x=Y(0,V(E.pos[0]-o,240-B[C].width));B[C].y=Y(0,V(E.pos[1]-p,240-B[C].height))
		elif E.type==A.KEYDOWN:
			if E.key==A.K_ESCAPE:P=M;D.clear()
			elif E.key==A.K_t and A.key.get_mods()&A.KMOD_CTRL:G={C:A.Rect(120,120,50,50),I:(0,0,0),K:1,b:J,F:H,O:A.Rect(0,0,0,0),L:C};D.append(G)
			elif E.key==A.K_e and A.key.get_mods()&A.KMOD_CTRL:A3();P=J
			elif E.key==A.K_y and A.key.get_mods()&A.KMOD_CTRL:i=J;X=J;Q=J
			elif E.key==A.K_o and A.key.get_mods()&A.KMOD_CTRL:
				try:A4(x.fileopenbox('Open file','Select File to convert to Rectangles'))
				except:v('Image Err')
			elif E.key==A.K_BACKSPACE:
				if B:
					if B[F]!=H:
						A9=D.copy()
						for G in A9:
							if G[F]==B[F]:D.remove(G)
					else:D.remove(B)
					B=H
			if B:
				if E.key==A.K_KP_PLUS:
					g=D.index(B)
					if g>0:D.remove(B);D.insert(g-1,B)
				elif E.key==A.K_KP_MINUS:
					g=D.index(B)
					if g<h(D)-1:D.remove(B);D.insert(g+1,B)
	A.draw.circle(N,(120,0,120),A7,A6,5);A.draw.rect(N,(120,255,120),A.Rect(119,0,2,240));A.draw.rect(N,(255,120,120),A.Rect(0,119,240,2))
	if i:A1()
	A.display.flip();A5.tick(y)
A.quit()
sys.exit()
