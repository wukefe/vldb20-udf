CREATE TABLE BLACKSCHOLES ( SPTPRICE   DECIMAL(15,6) NOT NULL,
                            STRIKE     DECIMAL(15,6) NOT NULL,
                            RATE       DECIMAL(15,6) NOT NULL,
                            DIVQ       DECIMAL(15,6) NOT NULL,
                            VOLATILITY DECIMAL(15,6) NOT NULL,
                            TIME       DECIMAL(15,6) NOT NULL,
                            OPTIONTYPE CHAR(1)       NOT NULL,
                            DIVS       DECIMAL(15,6) NOT NULL,
                            DGREFVAL   DECIMAL(15,6) NOT NULL);
