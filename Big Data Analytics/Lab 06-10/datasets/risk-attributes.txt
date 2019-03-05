Description of the attributes

Name of Attribute     Description
ORDER_ID              ID number of the online order
CLASS                 Class attribute of the task (yes/no)
                      (only contained in the training data)
B_EMAIL               was an email address submitted together with the order (yes/no)
B_TELEFON             was an phone number submitted together with the order (yes/no)
B_BIRTHDATE           Birth date, if submitted together with the order
FLAG_LRIDENTISCH      if address of delievery and invoice are identical then "yes" else "no"
FLAG_NEWSLETTER       was the E-Newsletter subscribed to together with the order (yes/no)
Z_METHODE             Selected method of payment
Z_CARD_ART            Selected type of card if payment by card is chosen
Z_CARD_VALID          Expiration date of the card in the form month.year
                      (e.g. 05.2006 meaning the card is valide till May 2006)
Z_LAST_NAME           is the name of the account or card holder identical with the name of
                      the delivery address (yes/no)
VALUE_ORDER           Value of the order in Euro
WEEKDAY_ORDER         Weekday of the order
TIME_ORDER            Time of the order
AMOUNT_ORDER          Number of ordered items
ANUMBER_01            Data field for the number of an ordered item
ANUMBER_02            Data field for the number of an ordered item
ANUMBER_03            Data field for the number of an ordered item
ANUMBER_04            Data field for the number of an ordered item
ANUMBER_05            Data field for the number of an ordered item
ANUMBER_06            Data field for the number of an ordered item
ANUMBER_07            Data field for the number of an ordered item
ANUMBER_08            Data field for the number of an ordered item
ANUMBER_09            Data field for the number of an ordered item
ANUMBER_10            Data field for the number of an ordered item
CHK_LADR              Orders with the same delivery address within 3 days (yes/no)
CHK_RADR              Orders with the same invoice address within 3 days (yes/no)
CHK_KTO               Orders with the same account number within 3 days (yes/no)
CHK_CARD              Orders with the same card number within 3 days (yes/no)
CHK_COOKIE            Orders with the same browser cookie within 3 days (yes/no)
CHK_IP                Orders with the same browser IP within 3 days (yes/no)
FAIL_LPLZ             Zip code of the delivery address unknown (yes/no)
FAIL_LORT             City of the delivery address unknown (yes/no)
FAIL_LPLZORTMATCH     Zip code and city of the delivery address do not fit together (yes/no)
FAIL_RPLZ             Zip code of the invoice address unknown (yes/no)
FAIL_RORT             City of the invoice address unknown (yes/no)
FAIL_RPLZORTMATCH     Zip code and city of the invoice address do not fit together (yes/no)
SESSION_TIME          Duration of the online session for the order in minutes
NEUKUNDE              is the ordering person a new custormer (yes/no)
AMOUNT_ORDER_PRE      Total number of items of previous orders, if available
VALUE_ORDER_PRE       Total value of previous orders, if available
DATE_LORDER           Date of the last order, if available
MAHN_AKT              Current stage of reminder of the customer, if available
MAHN_HOECHST          Highest stage of reminder of the customer occurred up to now, if available
