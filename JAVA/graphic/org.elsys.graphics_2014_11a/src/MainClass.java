//package org.elsys.graphics_2014_11a

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.MouseMoveListener;
import org.eclipse.swt.events.PaintEvent;
import org.eclipse.swt.events.PaintListener;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

public class MainClass {
	private static Point fp;
	private static Point lp;
	
	public static void main(String[] args) {
		Display d=new Display();
		Shell shell=new Shell(d);
		shell.setLayout(new FillLayout());
		
		Canvas c=new Canvas(shell, SWT.NONE);
		c.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_WHITE));
		shell.open();
		
		createPaintListener(c);
		createMouseListener(c);
		createMoveListener(c);
		while(!shell.isDisposed()) {
			if(!d.readAndDispatch()) {
				d.sleep();
			}
		}
		d.dispose();
	}

	private static void createMoveListener(final Canvas c) {
		c.addMouseMoveListener(new MouseMoveListener() {
			
			public void mouseMove(MouseEvent e) {
				if(fp!=null) {
					GC gc=new GC(c);
					if(lp!=null) {
						gc.setXORMode(true);
						gc.drawLine(fp.x, fp.y, lp.x, lp.y);
						lp=new Point(e.x, e.y);
						gc.drawLine(fp.x, fp.y, lp.x, lp.y);
					} else {
						lp=new Point(e.x, e.y);
					}
					gc.dispose();
				}
			}
		});
	}

	private static void createMouseListener(final Canvas c) {
		c.addMouseListener(new MouseListener() {
			
			public void mouseUp(MouseEvent e) {
			}
			
			public void mouseDown(MouseEvent e) {
				if(fp==null) {
					fp=new Point(e.x, e.y);
				} else {
					GC gc=new GC(c);
					gc.drawLine(fp.x, fp.y, e.x, e.y);
					gc.dispose();
					fp=null;
				}
			}
			
			public void mouseDoubleClick(MouseEvent e) {
				
			}
		});
	}

	private static void createPaintListener(Canvas c) {
		c.addPaintListener(new PaintListener() {
			
			public void paintControl(PaintEvent e) {
			}
		});
	}
}