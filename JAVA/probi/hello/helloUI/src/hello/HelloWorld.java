package hello;

import java.awt.Label;

public class HelloWorld {
	public static void main(String[] args) {
		Display display = new Display;
		Shell shell = new Shell(display);
		shell.setText("Hello World!");
		shell.setBounds(100,100,200,50);
		shell.setLayout(new FillLayout());
		Label label = new Label(shell, SWT.CENTER);
		label.setText("Hello World!");
		shell.open();
		while(!shell.isDisposed()) {
			if(!display.readAndDispatch()) {
				display.sleep();
			}
		display.dispose();
		}
	}
}
