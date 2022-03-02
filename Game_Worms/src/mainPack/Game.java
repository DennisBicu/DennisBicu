package mainPack;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferStrategy;
import java.util.Random;

public class Game extends Canvas implements Runnable {

	private static final long serialVersionUID = -7896182856386479492L;

	public static final int WIDTH = 640, HEIGHT = WIDTH/12 * 9;
	
	private static boolean alive = true;
	private static boolean victory = false;
	
	private Thread thread;
	private boolean running = false;
	
	private Handler handler;
	private Random r;
	private HUD hud;
	private Spawn spawner;
	
	
	public Game(){
		handler = new Handler();
		//Game knows to listen to the keyboard
		this.addKeyListener(new KeyInput(handler));
		
		new Window(WIDTH, HEIGHT, "Game #1", this);
		
		hud = new HUD();
		spawner = new Spawn(handler, hud);
			
		r = new Random();
		handler.addObject(new Player(WIDTH/2-32, (HEIGHT/2)-48, ID.Player, handler));
		handler.addObject(new BasicEnemy(r.nextInt(WIDTH - 32), r.nextInt(HEIGHT - 32), ID.BasicEnemy, handler));
		
	}
	
	public synchronized void start(){
		thread = new Thread(this);
		thread.start(); //starting the thread
		running = true;
	}
	
	public synchronized void stop(){
		try{
			thread.join(); //killing the thread
			running = false; 
		} catch (Exception e){
			e.printStackTrace();
		}
	}
	
	//A GAME LOOP - reusable
	public void run(){
		this.requestFocus();
		long lastTime = System.nanoTime();
		double amountOfTicks = 60.0;
		double ns = 1000000000 / amountOfTicks;
		double delta = 0;
		long timer = System.currentTimeMillis();
		int frames = 0;
		
		while(this.running){
			long now = System.nanoTime(); 
			delta = delta + (now - lastTime) / ns;
			lastTime = now;
			
			while (delta >= 1){
				tick();
				delta--;
			}
			
			if (this.running){
				render();
			}
			frames++;
			
			if(System.currentTimeMillis() - timer > 1000){
				timer = timer + 1000;
				System.out.println("FPS: " + frames);
				frames = 0;
			}
		}
		stop();
	}
	
	private void tick(){
		handler.tick();
		hud.tick();
		spawner.tick();
	}
		
	private void render(){
		BufferStrategy bs = this.getBufferStrategy();
		if (bs == null){
			this.createBufferStrategy(3);
			return;
		}
		
		Graphics g = bs.getDrawGraphics();
		g.setColor(Color.black);
		g.fillRect(0, 0, WIDTH, HEIGHT);
		
		//Handler running through every object and rendering it
		handler.render(g);
		
		hud.render(g);
		
		g.dispose();
		bs.show();
		
	}
	
	//if X or Y coordinates go past Min. or Max. (WIDTH, HEIGHT) then they will be set to Min/Max
	public static float clamp (float var, float min, float max){
		if (var >= max)
			return var = max;
		else if (var <= min) 
			return var = min;
		else 
			return var;
	}
	
	public static void main(String[] args) {
		new Game();
	}
	public static boolean getAlive() {
		return alive;
	}
	public static void setAlive(boolean alive) {
		Game.alive = alive;
	}

	public static boolean isVictory() {
		return victory;
	}

	public static void setVictory(boolean victory) {
		Game.victory = victory;
	}


}
