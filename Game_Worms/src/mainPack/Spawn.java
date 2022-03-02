package mainPack;

//import java.util.LinkedList;
import java.util.Random;

public class Spawn {
	private Handler handler;
	private HUD hud;
	private Random r = new Random();
	
	private int scoreKeep = 0;
	
	public Spawn(Handler handler, HUD hud){
		this.handler = handler;
		this.hud = hud;
	}
	
	public void tick(){
		if(scoreKeep == 2500){
			Game.setVictory(true);
		}
		scoreKeep++;
		while (Game.getAlive() && !Game.isVictory()){
		if(scoreKeep >= 200 && scoreKeep < 2500) {
			scoreKeep = 0;
			hud.setLevel(hud.getLevel()+1);
			
			switch(hud.getLevel()){
			
			case 2:{
				handler.addObject(new BasicEnemy(r.nextInt(Game.WIDTH - 50), r.nextInt(Game.HEIGHT - 50), ID.BasicEnemy, handler));
				break;
			}
			
			case 3:{
				handler.addObject(new BasicEnemy(r.nextInt(Game.WIDTH - 50), r.nextInt(Game.HEIGHT - 50), ID.BasicEnemy, handler));
				
				break;
			}
				
			case 4:{
				handler.addObject(new FastEnemy(r.nextInt(Game.WIDTH-32), r.nextInt(Game.HEIGHT-32), ID.FastEnemy, handler));
				
				break;
			}
			
			case 5:{
				handler.addObject(new SmartEnemy(r.nextInt(Game.WIDTH - 32), r.nextInt(Game.HEIGHT - 32), ID.SmartEnemy, handler));
				break;
			}
			
			case 6:{
				handler.addObject(new FastEnemy(r.nextInt(Game.WIDTH-32), r.nextInt(Game.HEIGHT-32), ID.FastEnemy, handler));
				break;
			}
			
			case 10:{
				handler.clearWave();
				handler.addObject(new BossEnemy(Game.WIDTH/2 - 64, -100, ID.BossEnemy, handler));
				GameObject tempObject = null;
				for (int i = 0; i < handler.objectList.size(); i++){
					tempObject = handler.objectList.get(i);
					if (tempObject.getID() == ID.Player){
						tempObject.setY((int)Game.clamp(tempObject.getY(), Game.HEIGHT - 32, handler.objectList.getLast().getY()));
					}
				}
				
				break;
			}
				
				default:{
					break;
				}
			}
		}
		}
				
	}
	

	
	public void spawnWave(Handler handler, int level){
		for (int i = 0; i < level; i++){
			handler.addObject(new BasicEnemy(r.nextInt(Game.WIDTH - 50), r.nextInt(Game.HEIGHT - 50), ID.BasicEnemy, handler));
		}
	}
}
