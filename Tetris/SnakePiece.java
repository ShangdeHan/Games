package hw4;
/**
 * @author shangde Han
 */
import api.Cell;
import api.Position;
import api.Icon;

/**
 * This class is SnakePiece class, a subclass of AbstractPiece 
 * to create a SnakePiece
 */
public class SnakePiece extends AbstractPiece{
	/**
	 * create an array of Position objects
	 * each index is a possible position each cell
	 */
	private static final Position[] sequence =
		{
		new Position(0, 0),
		new Position(0, 1),
		new Position(0, 2),
		new Position(1, 2),
		new Position(1, 1),
		new Position(1, 0),
		new Position(2, 0),
		new Position(2, 1),
		new Position(2, 2),
		new Position(1, 2),
		new Position(1, 1),
		new Position(1, 0),
		};
	
	/**
	 * counter how many times transform() method
	 * has been called
	 */
	private int counter;
	
	/**
	 * inherits from AbstractPiece class
	 * @throws java.io.IllegalArgumentException
	 * thorws IllegalArgumentException if givenicons' length does not equal to 4
	 */
	public SnakePiece(Position givenPosition, Icon[] icons) throws IllegalArgumentException {
		super(givenPosition, icons);
		if(icons.length!=4) {
			throw new IllegalArgumentException("icons' length is not equal to 4");
		}
		counter = 1;
		Cell[] localCells = new Cell[icons.length];
		localCells[0] = new Cell(icons[0], new Position(0, 0));
		localCells[1] = new Cell(icons[1], new Position(1, 0));
		localCells[2] = new Cell(icons[2], new Position(1, 1));
		localCells[3] = new Cell(icons[3], new Position(1, 2));
	    setCells(localCells);
	}
	
	 /**
	   * Transforms this piece without altering its position
	   * according to the rules of the game to be implemented.  
	   * Typical operations would be rotation or reflection. 
	   * No bounds checking is done.
	   * abstracts this method, so in subclasses there are detailed method
	   * 
	   * this method transitions through twelve different states and back to the original
	   */   
	public void transform() {
		Cell[] cells = new Cell[getCells().length];
		for(int i = 0; i<cells.length;i++) {
			cells[i] = getCells()[i];
		}
		if(counter >2) {
			cells[0].setPosition(sequence[counter]);
			cells[1].setPosition(sequence[counter-1]);
			cells[2].setPosition(sequence[counter-2]);
			cells[3].setPosition(sequence[counter-3]);
		}else if(counter == 2) {
			cells[0].setPosition(sequence[2]);
			cells[1].setPosition(sequence[1]);
			cells[2].setPosition(sequence[0]);
			cells[3].setPosition(sequence[11]);
		}else if(counter == 1) {
			cells[0].setPosition(sequence[1]);
			cells[1].setPosition(sequence[0]);
			cells[2].setPosition(sequence[11]);
			cells[3].setPosition(sequence[10]);
		}else if(counter == 0) {
			cells[0].setPosition(sequence[0]);
			cells[1].setPosition(sequence[11]);
			cells[2].setPosition(sequence[10]);
			cells[3].setPosition(sequence[9]);
		}if(counter ==11) {
			counter = -1;
		}counter++;
		setCells(cells);
	}
}
