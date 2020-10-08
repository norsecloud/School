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

public class TimeButtonDemo extends Application {

  protected BorderPane getPane() {
    
    BorderPane pane = new BorderPane(); // pane for containing buttons and clock  
  
    HBox paneForButtons = new HBox(50); // pane for containing buttons    
     
    // write code for buttons 
    //button variables
    Button bt12hr = new Button("12 Hr");
    Button bt24hr = new Button("24 Hr");
    //image variables
    Image image00 = new Image("usa.jpg");
    Image image01 = new Image("eu.jpg");
    //image 
    ImageView imageView2 = new ImageView(image00);
    imageView2.setFitHeight(100);
    imageView2.setFitWidth(100);
    pane.getChildren().add(imageView2); 
    paneForButtons.getChildren().addAll(bt12hr, bt24hr);
    paneForButtons.setAlignment(Pos.CENTER);
    paneForButtons.setStyle("-fx-border-color: black");

    pane.setBottom(paneForButtons);
    
    
    DigitalClock clock = new DigitalClock();  // clock to be added to pane
    
    // handle button clicks with lambdas
    
    // handle keyboard presses with lambdas
     
    return pane;
  }
  
  public void start(Stage primaryStage) {
    // Create a scene and place it in the stage
    Scene scene = new Scene(getPane(),250, 150);
    primaryStage.setTitle("ClockApplication"); // Set the stage title
    primaryStage.setScene(scene); // Place the scene in the stage
    primaryStage.show(); // Display the stage
  }

  public static void main(String[] args) {
    launch(args);
  }
}

class DigitalClock extends Label 
{

    private SimpleDateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
    private Timeline animation;
    private Calendar time;
    
    public DigitalClock() 
    {
        // get time and set text with lambda
        int hour = time.get(time.HOUR_OF_DAY);
        int minute = time.get(time.MINUTE);
        int second = time.get(time.SECOND);
        // change text font here
        
        // set animation here
        
        //path transitions
    }//end DigitalClock
    
    public void changeFormat24()
    {
        // write code here for changing to 24 hour clock
    }//end void changeFormat24()
    
    public void changeFormat12()
    {
        // write code here for changing to 12 hour clock
    }//end void changeFormat12()
              
}//end class DigitalClock
//end prog