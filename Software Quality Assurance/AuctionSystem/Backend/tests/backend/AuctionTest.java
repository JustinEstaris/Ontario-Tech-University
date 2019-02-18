package tests.backend;

import backend.Auction;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

public class AuctionTest {
    /**
     * Test of getItemName method, of class Auction.
     */
    @Test
    public void testGetItemName() {
        System.out.println("Testing getItemName()...");
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);
        String expResult = "itemname";
        String result = instance.getItemName();
        assertEquals(expResult, result);
    }

    /**
     * Test of getSellerName method, of class Auction.
     */
    @Test
    public void testGetSellerName() {
        System.out.println("Testing getSellerName()...");
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);
        String expResult = "test";
        String result = instance.getSellerName();
        assertEquals(expResult, result);
    }

    /**
     * Test of getBuyerName method, of class Auction.
     */
    @Test
    public void testGetBuyerName() {
        System.out.println("Testing getSellerName()...");
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);
        String expResult = "test";
        String result = instance.getBuyerName();
        assertEquals(expResult, result);
    }

    /**
     * Test of getHighestBid method, of class Auction.
     */
    @Test
    public void testGetHighestBid() {
        System.out.println("Testing getSellerName()...");
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);
        double expResult = 1.0;
        double result = instance.getHighestBid();
        assertEquals(expResult, result, 0.0);
    }

    /**
     * Test of getDaysRemaining method, of class Auction.
     */
    @Test
    public void testGetDaysRemaining() {
        System.out.println("Testing getDaysRemaining()...");
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);
        int expResult = 1;
        int result = instance.getDaysRemaining();
        assertEquals(expResult, result);
    }

    /**
     * Test of setDaysRemaining method, of class Auction.
     */
    @Test
    public void testSetDaysRemaining() {
        System.out.println("Testing setDaysRemaining()...");
        int days = 5;
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);
        instance.setDaysRemaining(days);
        int expResult = 5;
        int result = instance.getDaysRemaining();
        assertEquals(expResult, result);
    }

    /**
     * Test of newBid method, of class Auction.
     */
    @Test
    public void testNewBid() {
        System.out.println("Testing newBid()...");
        String buyer = "test2";
        double bid = 5.0;
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);
        instance.newBid(buyer, bid);
        
        double expResult = 5.0;
        double result = instance.getHighestBid();
        assertEquals(expResult, result, 0.0);
        
        String expResult2 = "test2";
        String result2 = instance.getBuyerName();
        assertEquals(expResult2, result2);
    }

    /**
     * Test of formatOutput method, of class Auction.
     */
    @Test
    public void testFormatOutput() {
        System.out.println("Tesing formatOutput()...");
        Auction instance = new Auction("itemname", "test", "test", 1, 1.0);  
        String expResult = "itemname                  test            test            001 001.00";
        String result = instance.formatOutput();
        assertEquals(expResult, result);
    }
}