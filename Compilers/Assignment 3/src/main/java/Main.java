import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import static java.lang.System.out;
import java.util.*;

public class Main {
    static class ThrowingErrorListener extends BaseErrorListener { 
        public static final ThrowingErrorListener INSTANCE 
            = new ThrowingErrorListener(); 
        @Override 
        public void syntaxError(
                Recognizer<?, ?> recognizer, 
                Object offendingSymbol, 
                int line, 
                int charPositionInLine, 
                String msg, 
                RecognitionException e) 
            throws ParseCancellationException { 
            throw new ParseCancellationException(
                    "line "
                    + line
                    + ":"
                    + charPositionInLine + " " + msg); 
        } 
    }

    public static ProgramParser.ProgramContext parse(String filename) throws Exception {
        ProgramLexer lexer = new ProgramLexer(CharStreams.fromFileName(filename));
        lexer.removeErrorListeners();
        lexer.addErrorListener(ThrowingErrorListener.INSTANCE);

        CommonTokenStream tokens = new CommonTokenStream(lexer);
        ProgramParser parser = new ProgramParser(tokens);
        parser.removeErrorListeners();
        parser.addErrorListener(ThrowingErrorListener.INSTANCE);

        // Start parsing
        return parser.program();
    }

    public static void run(String filename) throws Exception {
        parse(filename).code.eval(new HashMap<String, Double>());
    }

    public static void main(String[] args) {
        try {
            for(String name : args) {
                run(name);
            }
        } catch(Exception e) {
            out.println("Error:" + e.getMessage());
            e.printStackTrace();
        }
    }
}
