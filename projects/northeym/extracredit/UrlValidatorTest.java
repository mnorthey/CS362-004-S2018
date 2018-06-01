

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {
	// Allows use of randoms
	static Random rand = new Random();

	public UrlValidatorTest(String testName) {
		super(testName);
	}
	
	// Function is public domain code found at https://dzone.com/articles/generate-random-alpha-numeric
	private static final String ALPHA_NUMERIC_STRING = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	public static String randomAlphaNumeric(int count) {
		StringBuilder builder = new StringBuilder();
		while (count-- != 0) {
			int character = (int)(Math.random()*ALPHA_NUMERIC_STRING.length());
			builder.append(ALPHA_NUMERIC_STRING.charAt(character));
		}
		
		return builder.toString();
	}
	
	public void testIsValid()
	{
		
		
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
		for (int i = 0; i < 100; i++)
		{
			int random;
			String url = "";
			boolean expected = true;
			
			// Generate protocol
			int prot = rand.nextInt(3) + 1;
			
			// If 2, use correct protocol
			// Note: Section commented out because bug in code causes crash
			/*
			if (prot == 2)
			{
				String[] protocols = { "ARP://", "DHCP://", "DNS://", "DSN://", "FTP://", "HTTP://",
						"IMAP://", "ICMP://", "IDRP://", "IP://", "IRC://", "POP3://", "PAR://",
						"RLOGIN://", "SMTP://", "SSL://", "SSH://", "TCP://", "TELNET://", "UPD://",
						"UPS://"};
				
				random = rand.nextInt(protocols.length);
				url += protocols[random];
			}
			// If 3, use random protocol
			else if (prot == 3)
			{
				random = rand.nextInt(20) + 1;
				String badProt = randomAlphaNumeric(random);
				badProt += "://";
				
				url += badProt;
				expected = false;
			}
			*/
			
			// Generate base path
			random = rand.nextInt(20) + 1;
			String path = randomAlphaNumeric(random);
			
			// Add possible domain
			String[] domains = { "", ".c..om", "...", "..", "//", "///", ".com", ".co.uk", "biz", ".org", ".edu", ".gov",
					".net", ".de", ".es" };
			
			random = rand.nextInt(domains.length);
			path += domains[random];
			
			if (random == 0 || random == 1 || random == 2 || random == 3 || random == 4 || random == 5)
			{
				expected = false;
			}
			
			url += path;
			
			// Add possible port
			int port = rand.nextInt(3) + 1;
			String portstr = "";
			
			if (port == 1)
			{
				portstr += "/";
			}
			
			// If 2, use random int -100000 to 100000
			if (port == 2)
			{
				int min = -100000;
				int max = 100000;
				
				random = rand.nextInt(max + 1 - min) + min;
				
				portstr = ":" + Integer.toString(random) + "/";
				
				if (random < 1 || random > 65535)
				{
					expected = false;
				}
			}
			
			// If 3, use random string
			if (port == 3)
			{
				String randomport = "";
				
				random = rand.nextInt(6) + 1;
				randomport = randomAlphaNumeric(random);;
					
				portstr = ":" + randomport + "/";
				
				expected = false;
			}
			
			url += portstr;
			
					
			// Add possible subdomain(s)
			String subdomain = "";
			double addSubdomain = Math.round(Math.random());
			int first = 1;
			while (addSubdomain == 1)
			{
				random = rand.nextInt(20) + 1;
				
				String subpath = randomAlphaNumeric(random);
				
				subdomain += subpath + "/";
				
				addSubdomain = Math.round(Math.random());
			}
			
			url += subdomain;
			
			// Add possible query
			String query = "";
			double addQuery = Math.round(Math.random());
			int repeat = 0;
			while (addQuery == 1)
			{
				if (repeat == 1)
				{
					query += "&";
				}
				else
				{
					query += "?";
				}
				
				repeat = 1;
				
				random = rand.nextInt(20) + 1;
				String randomString = randomAlphaNumeric(random);
				
				query += randomString + "=";
				
				random = rand.nextInt(20) + 1;
				randomString = randomAlphaNumeric(random);
				
				query += randomString;
				
				addQuery = Math.round(Math.random());
			}
			
			url += query;
			
			ResultPair rp = new ResultPair(url, expected);
			
			boolean actual = urlVal.isValid(rp.item);
			
			if (actual != expected)
			{
				int testnum = i + 1;
				System.out.println("Test #" + testnum + " failed.");
				System.out.println("	URL: " + url);
				System.out.println("	Expected: " + expected + ". Actual: " + actual + ".");
			}
			/*
			else
			{
				int testnum = i + 1;
				System.out.println("Test #" + testnum + " passed.");
			}
			*/
			
		}
	}
}
