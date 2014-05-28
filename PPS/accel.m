function [ax, ay]=accel(x, y, vx, vy)
	ax=0.0;
	ay=-9.8;
	
	v=sqrt(vx^2+vy^2);
	ar_x=-0.1*vx*v;
	ar_y=-0.1*vy*v;
	
	ax+=ar_x;
	ay+=ar_y;
end
