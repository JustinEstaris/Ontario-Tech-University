import org.junit.*;
import static org.junit.Assert.*;
import org.antlr.v4.runtime.*;
import java.nio.file.*;
import java.io.*;

public class TestParser {
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;
    private final PrintStream originalErr = System.err;

    @Before
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
    }

    @After
    public void restoreStreams() {
        System.setOut(originalOut);
        System.setErr(originalErr);
    }


    static String readFile(String path) throws IOException {
        StringBuilder s = new StringBuilder();
        String line;
        BufferedReader reader = new BufferedReader(new FileReader(path));
        reader.lines().forEach( x -> {s.append(x + "\n");} );
        reader.close();

        return s.toString();
    }

    public void testParse(String name) {
        String filename = name + ".expr";
        try {
            Main.parse(filename);
            assertTrue(true);
        } catch(Exception e) {
            assertTrue(e.getMessage(), false);
        }

    }

    public void testRun(String name) {
        String filename = name + ".expr";
        String expectedOutputFile = name + ".out";
        try {
            Main.run(filename);
            String output = outContent.toString().trim();
            String expected = readFile(expectedOutputFile).trim();

            assertEquals(output, expected);
        } catch(Exception e) {
            fail("Parser error \"" + filename + "\": " + e.getMessage());
        }
    }

    @Test
    public void testSyntax1() {
        testParse("program_1");
    }
    @Test
    public void testRun1() {
        testRun("program_1");
    }

    @Test
    public void testSyntax2() {
        testParse("program_2");
    }
    @Test
    public void testRun2() {
        testRun("program_2");
    }

    @Test
    public void testSyntax3() {
        testParse("program_3");
    }
    @Test
    public void testRun3() {
        testRun("program_3");
    }

    @Test
    public void testSyntax4() {
        testParse("program_4");
    }
    @Test
    public void testRun4() {
        testRun("program_4");
    }

    @Test
    public void testSyntax5() {
        testParse("program_5");
    }
    @Test
    public void testRun5() {
        testRun("program_5");
    }

    @Test
    public void testSyntax6() {
        testParse("program_6");
    }
    @Test
    public void testRun6() {
        testRun("program_6");
    }

    @Test
    public void testSyntax7() {
        testParse("program_7");
    }
    @Test
    public void testRun7() {
        testRun("program_7");
    }

    @Test
    public void testSyntax8() {
        testParse("program_8");
    }
    @Test
    public void testRun8() {
        testRun("program_8");
    }

    @Test
    public void testSyntax9() {
        testParse("program_9");
    }
    @Test
    public void testRun9() {
        testRun("program_9");
    }

    @Test
    public void testSyntax10() {
        testParse("program_10");
    }
    @Test
    public void testRun10() {
        testRun("program_10");
    }
}
