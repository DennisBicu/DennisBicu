package mainPack;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class KeyInput extends KeyAdapter{

	private Handler handler;
	
	private boolean[] keyDown = new boolean[4];
	//keyDown[0] == W, 
	//keyDown[1] == A,
	//keyDown[2] == S,
	//keyDown[3] == D
	
	
	public KeyInput(Handler handler){
		this.handler = handler;
		for(int i = 0; i < keyDown.length; i++){
			keyDown[i] = false;
		}
		
	}
	
	public void keyPressed(KeyEvent e){//method from the KeyEvent class that deals with what happens on the press of certain keys
		int key = e.getKeyCode(); //when pressing a Keyboard input, it will transmit the correspondent number value
		//System.out.println(key);
		for (int i = 0; i < handler.objectList.size(); i++){
			GameObject tempObject = handler.objectList.get(i);
			if (tempObject.getID() == ID.Player){	
				if (key == KeyEvent.VK_W){
					tempObject.setVelY(-5);
					keyDown[0] = true; //the key is pressed and the velocity is set 
				}
				if (key == KeyEvent.VK_A){
					tempObject.setVelX(-5);
					keyDown[1] = true;
				}
				if (key == KeyEvent.VK_S){
					tempObject.setVelY(5);
					keyDown[2] = true;
				}
				if (key == KeyEvent.VK_D){
					tempObject.setVelX(5);
					keyDown[3] = true;
				}
				if (key == KeyEvent.VK_ESCAPE){
					System.exit(1);
				}
			}
		}
		
	}
	
	public void keyReleased(KeyEvent e){ //method from the KeyEvent class that deals with what happens on the release of certain keys
		int key = e.getKeyCode();
		
		for (int i = 0; i < handler.objectList.size(); i++){
			GameObject tempObject = handler.objectList.get(i);
			if (tempObject.getID() == ID.Player){
				//the bool keyDown is set to false because the key is no longer pressed (it's released)
				if (key == KeyEvent.VK_W) keyDown[0] = false; 
				if (key == KeyEvent.VK_A) keyDown[1] = false; 
				if (key == KeyEvent.VK_S) keyDown[2] = false; 
				if (key == KeyEvent.VK_D) keyDown[3] = false; 
				
				//vertical movement
				if(!keyDown[0] && !keyDown[2]){ //if W and S are NOT pressed then velocity = 0;
					tempObject.setVelY(0);
				}
				//horizontal movement
				if(!keyDown[1] && !keyDown[3]){ //if A and D are NOT pressed then velocity = 0
					tempObject.setVelX(0);
				}
			}
			
		}
	}
	
}
