import javafx.application.Application;
import javafx.stage.Stage;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;

import javafx.animation.Timeline;
import javafx.animation.KeyFrame;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.util.Duration;

import java.util.Calendar;
import javafx.scene.control.Label;
import java.text.SimpleDateFormat;
import javafx.scene.input.KeyCode;

import javafx.scene.paint.Color;
import javafx.scene.text.Font;

public class TimeButtonDemo001 extends Application 
{

  protected BorderPane getPane() 
  {
    
    BorderPane pane = new BorderPane(); // pane for containing buttons and clock  
  
    HBox paneForButtons = new HBox(50); // pane for containing buttons    
     
    // write code for buttons 
    //12 hour button
    Button btn12Hr = new Button ("12 Hr");
    //US flag image for btn12Hr
    Image imageUS = new Image("usa.jpg");
    ImageView imageV00 = new ImageView(imageUS);
    imageV00.setFitWidth(40);
    imageV00.setFitHeight(40);
    btn12Hr.setGraphic(imageV00);
    
    //24 hour button
    Button btn24Hr = new Button ("24 Hr");
    //EU flag image for btn12Hr
    Image imageEU = new Image("eu.jpg");
    ImageView imageV01 = new ImageView(imageEU);
    imageV00.setFitWidth(40);
    imageV00.setFitHeight(40);
    btn24Hr.setGraphic(imageV01);
    
    //green border pane above the buttons
    paneForButtons.setStyle("-fx-border-style: solid inside;" + "-fx-border-width: 2;" + "-fx-border-color:green;");
    //add buttons to pane
    paneForButtons.getChildren().addAll(btn12Hr, btn24Hr);
    //add button pane to main pane
    pane.setBottom(paneForButtons);
    
    DigitalClock clock = new DigitalClock();  // clock to be added to pane
    
    // handle button clicks with lambdas
    
    //btn12hr changes clock to 12 hour
    btn12Hr.setOnAction(e ->{
    	clock.changeFormat12();
    });//end btn12hr.setaction
    
  //btn24hr changes clock to 24 hour
    btn24Hr.setOnAction(e ->{
    	clock.changeFormat24();
    });//end btn24hr.setaction
    
    // handle keyboard presses with lambdas
    pane.setOnKeyPressed(e ->{
    	if(e.getCode() == KeyCode.UP)
    	{//changes text color to RED when UP arrow pressed
    		clock.setTextFill(Color.RED);
    	}//end if
    	
    	else if(e.getCode() == KeyCode.DOWN)
    	{//changes text color to CYAN when DOWN arrow pressed
    		clock.setTextFill(Color.CYAN);
    	}//end if
    	
    	else if(e.getCode() == KeyCode.ENTER)
    	{//changes text color to BLACK when DOWN arrow pressed
    		clock.setTextFill(Color.BLACK);
    	}//end if
    });//end pane.setOnKeyPressed
    return pane;
  }//end protected BorderPane getPane()
  
  public void start(Stage primaryStage) 
  {
    // Create a scene and place it in the stage
    Scene scene = new Scene(getPane(),250, 150);
    primaryStage.setTitle("ClockApplication"); // Set the stage title
    primaryStage.setScene(scene); // Place the scene in the stage
    primaryStage.show(); // Display the stage
  }//end void start

  public static void main(String[] args) 
  {
    launch(args);
  }//end main
}//end public class TimeButtonDemo extends Application

class DigitalClock extends Label 
{
	//DigitalClock variables
    private SimpleDateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
    private Timeline animation;
    private Calendar time;
    
    public DigitalClock() 
    {
        // get time and set text with lambda
        time = Calendar.getInstance();
        setText(dateFormat.format(time.getTime()));
        
        // change text font here
        setFont(new Font("Arial",30));
        
        // set animation here
        animation = new Timeline(new KeyFrame(Duration.seconds(0.1),e->
        {
        	//update time
        	time.setTime(Calendar.getInstance().getTime());
        	//set time
        	setText(dateFormat.format(time.getTime()));
        }));
        
        //animation cycle loop INDEFINTINE basically goes on forever
        animation.setCycleCount(Timeline.INDEFINITE);
        
        //animation start
        animation.play();
        
        //path transitions
    }//end DigitalClock
    
    public void changeFormat24()
    {
        // write code here for changing to 24 hour clock
    	dateFormat = new SimpleDateFormat("HH:mm:ss");
    }//end void changeFormat24()
    
    public void changeFormat12()
    {
        // write code here for changing to 12 hour clock
    	dateFormat = new SimpleDateFormat("hh:mm:ss a");
    }//end void changeFormat12()
              
}//end class DigitalClock
//end prog