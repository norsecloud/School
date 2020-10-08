import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class javafxPractice extends Application 
//implements EventHandler<ActionEvent> this is for the commented out void handle
{
	Button bt;
	
	public static void main(String[] args)
	{
		launch(args);
	}//end main
	
	@Override
	public void start(Stage primaryStage) throws Exception
	{
		primaryStage.setTitle("Title Bitch");
		
		bt = new Button();
		bt.setText("uSuck");
		
		bt.setOnAction(e -> System.out.println("punk bitch"));
		
		StackPane layout = new StackPane();
		layout.getChildren().add(bt);
		
		Scene scene = new Scene(layout, 300, 250);
		primaryStage.setScene(scene);
		primaryStage.show();
				
	}
	/*
	@Override
	public void handle(ActionEvent event)
	{
		if(event.getSource()==bt)
		{
			System.out.println("hahhemasdw");
		}
	}
	*/

}//end javafxPractice
