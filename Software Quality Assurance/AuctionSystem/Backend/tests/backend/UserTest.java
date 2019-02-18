package tests.backend;

import backend.User;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

public class UserTest {

    /**
     * Test of getUsername method, of class User.
     */
    @Test
    public void testGetUsername() {
        System.out.println("Testing getUsername()...");
        User instance = new User("admin01", "AA", 0);
        String expResult = "admin01";
        String result = instance.getUsername();
        assertEquals(expResult, result);
    }
    
    /**
     * Test of getAccountType method, of class User.
     */
    @Test
    public void testGetAccountType() {
        System.out.println("Testing getAccountType()...");
        User instance = new User("admin01", "AA", 0);
        String expResult = "AA";
        String result = instance.getAccountType();
        assertEquals(expResult, result);
    }
    
    /**
     * Test of getCreditAmount method, of class User.
     */
    @Test
    public void testGetCreditAmount() {
        System.out.println("Testing getCreditAmount()...");
        User instance = new User("admin01", "AA", 100.00);
        double expResult = 100.00;
        double result = instance.getCreditAmount();
        assertEquals(expResult, result, 0.0);
    }
    
    /**
     * Test of setUsername method, of class User.
     */
    @Test
    public void testSetUsername() {
        System.out.println("Testing setUsername()...");
        String username = "newUserName";
        User instance = new User("originalUsername", "AA", 0.0);
        instance.setUsername(username);
        
        String expResult = username;
        String result = instance.getUsername();
        assertEquals(expResult, result);
    }
    
    
    /**
     * Test of setAccountType method, of class User.
     */
    @Test
    public void testSetAccountType() {
        System.out.println("Testing setAccountType()...");
        String accountType = "AA";
        User instance = new User("testUser", "FS", 0.0); // Change from FS to AA
        instance.setAccountType(accountType);

        String expResult = accountType;
        String result = instance.getAccountType();
        assertEquals(expResult, result);
    }
    
    
    /**
     * Test of setCreditAmount method, of class User.
     */
    @Test
    public void testSetCreditAmount() {
        System.out.println("Testing setCreditAmount()...");
        double creditAmount = 100.00;
        User instance = new User("admin01", "AA", 0.0); // Change from 0.0 credit to 100.00 credit
        instance.setCreditAmount(creditAmount);
        
        double expResult = creditAmount;
        double result = instance.getCreditAmount();
        assertEquals(expResult, result, 0.0);
    }


    /**
     * Test of updateCreditAmount method, of class User.
     */
    @Test
    public void testUpdateCreditAmount() {
        System.out.println("Testing updateCreditAmount()...");
        
        // TEST - INCREASE CREDIT AMOUNT \\
        double credit = 100.00;
        User instance = new User("admin01", "AA", 50.00);
        instance.updateCreditAmount(credit);
        
        double expResult = 150.00;
        double result = instance.getCreditAmount();
        assertEquals(expResult, result, 0.0);
        
        // TEST - DECREASE CREDIT AMOUNT \\
        credit = -100.00;
        instance.updateCreditAmount(credit);
        expResult = 50.00;
        result = instance.getCreditAmount();
        assertEquals(expResult, result, 0.0); 
    }

    /**
     * Test of formatOutput method, of class User.
     */
    @Test
    public void testFormatOutput() {
        System.out.println("Testing formatOutput()...");
        User instance = new User("admin01", "AA", 100.00);
        String expResult = String.format("%1$" + -15 + "s", "admin01") + " AA " + String.format("%09.2f", 100.00);
        String result = instance.formatOutput();
        assertEquals(expResult, result);
    }
    
}
