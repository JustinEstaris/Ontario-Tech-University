package tests.backend;

import backend.Users;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

import backend.Auctions;
import java.io.IOException;

public class UsersTest {
    /**
     * Test of validateDouble method, of class Users.
     */
    @Test
    public void testValidateDouble() {
        System.out.println("validateDouble");
        String doubleStr = "0.0";
        Users instance = new Users();
        double expResult = 0.0;
        double result = instance.validateDouble(doubleStr);
        assertEquals(expResult, result, 0.0);
    }

    /**
     * Test of load method, of class Users.
     */
    @Test
    public void testLoad() {
        System.out.println("load");
        String filename = "usernames.txt";
        Users instance = new Users();
        instance.load(filename);
    }

    /**
     * Test of createUser method, of class Users.
     */
    @Test
    public void testCreateUser() {
        System.out.println("createUser");
        String transaction = "01 ss02            SS 01765.00";
        Users instance = new Users();
        instance.createUser(transaction);
    }

    /**
     * Test of deleteUser method, of class Users.
     */
    @Test
    public void testDeleteUser() throws IOException {
        System.out.println("deleteUser");
        String transaction = "02 ss01            SS 00099.99";
        Users instance = new Users();
        instance.load("usernames.txt");
        Auctions auctions = new Auctions();
        instance.deleteUser(transaction, auctions);
    }

    /**
     * Test of refund method, of class Users.
     */
    @Test
    public void testRefund() {
        System.out.println("refund");
        String transaction = "05 BS TestUser      TestUser2       00500.00";
        Users instance = new Users();
        instance.load("usernames.txt");
        instance.refund(transaction);
    }

    /**
     * Test of addCredit method, of class Users.
     */
    @Test
    public void testAddCredit() {
        System.out.println("addCredit");
        String transaction = "06 AdminTestUser   AA 000005.00";
        Users instance = new Users();
        instance.load("usernames.txt");
        instance.addCredit(transaction);
    }

    /**
     * Test of closeAuction method, of class Users.
     */
    @Test
    public void testCloseAuction() {
        System.out.println("closeAuction");
        String buyer = "BSTestUser";
        String seller = "TestUser2";
        double amount = 5.0;
        Users instance = new Users();
        instance.load("usernames.txt");
        instance.closeAuction(buyer, seller, amount);

    }

    /**
     * Test of write method, of class Users.
     */
    @Test
    public void testWrite() throws Exception {
        System.out.println("write");
        String filename = "outUser.txt";
        Users instance = new Users();
        instance.load("usernames.txt");
        instance.write(filename);
    }
    
}
