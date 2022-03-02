package mainPack;

import java.awt.Graphics;
import java.util.LinkedList;

public class Handler {
	
	LinkedList<GameObject> objectList = new LinkedList<GameObject>(); //creating a LinkedList with members of the GameObject type
	
	public void tick(){
		GameObject tempObject = null;
		for (int i = 0; i < objectList.size(); i++){ //going through the linked list
			tempObject = objectList.get(i); 
			
			tempObject.tick();
		}
	}
	
	public void render (Graphics g){
		GameObject tempObject = null;
		for (int i = 0; i < objectList.size(); i++){
			tempObject = objectList.get(i);
			
			tempObject.render(g);
		}
	}
	
	public void addObject(GameObject object){
		this.objectList.add(object); //adding an object to the linked list
	}
	
	public void removeObject(GameObject object){
		this.objectList.remove(object); //removing an object from the linked list
	}
	
	public void clearWave(){
		GameObject tempObject = null;
		for (int i = 0; i < objectList.size(); i++){
			tempObject = objectList.get(i);
			if (tempObject.getID() == ID.Player){
				objectList.clear();
				objectList.add(tempObject);
			}
		}
	}
	
}
