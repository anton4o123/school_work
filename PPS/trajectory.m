format long
m=str2num(argv(){1});
rx=str2num(argv(){2});
ry=str2num(argv(){3});
angle_=str2num(argv(){4});
v0=str2num(argv(){5});
dt=str2num(argv(){6});
dc=str2num(argv(){7});
option=str2num(argv(){8});

if(option==1)
	a=str2num(argv(){9})*str2num(argv(){9})*pi;
else
	if(option==2)
		a=str2num(argv(){9})*str2num(argv(){9})
	else
		a=str2num(argv(){9})*str2num(argv(){10})
	end
end

if(angle_==90 || angle_==270)
	vx=0;
	vy=v0*sin(angle_*pi/180.0);
else
	if(angle_==0 || angle_==180 || angle_==360)
		vx=v0*cos(angle_*pi/180.0);
		vy=0;
	else
		vx=v0*cos(angle_*pi/180.0);
		vy=v0*sin(angle_*pi/180.0);
	end
end

fx=-0.5*1.225*vx*vx*dc*a;
fy=-m*9.8+0.5*1.225*vy*vy*dc*a;

vrxv=[rx];
vryv=[ry];

t=0;
while(ry>0)
	t+=dt;
	rx+=(vx/m)*dt;
	ry+=(vy/m)*dt;
	vx+=(fx/m)*dt;
	vy+=(fy/m)*dt;
	
	vrxv=[vrxv rx];
	vryv=[vryv ry];
	
	fx=-0.5*1.225*vx*vx*dc*a;
	fy=-m*9.8+0.5*1.225*vy*vy*dc*a;
end

rx+=0
ry+=0
t+=0
plot(vrxv, vryv)
pause
