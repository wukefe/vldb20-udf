import os
import logging
import numpy as np
import datetime as dt

def discount_price(extprice, disc):
    return extprice * (1 - disc)

def discount_taxprice(extprice, disc, tax):
    return discount_price(extprice, disc) * (1 + tax)

def profit_amount(extprice, disc, suppcost, qty):
    return extprice * (1 - disc) - suppcost * qty

def promo_disc(ptype, extprice, disc):
    val = []
    for id,typ in enumerate(ptype):
        if typ.startswith('PROMO'):   # ptype like 'PROMO%'
            val.append(discount_price(extprice[id], disc[id]))
        else:
            val.append(0)
    return val

def demo_q14():
    ptype = ["PROMOnice", "Dummyhello", "PROMOcool"]
    extprice = [1.2, 1.3, 1.5]
    disc = [0.3, 0.4, 0.5]
    print promo_disc(np.asarray(ptype), np.asarray(extprice), np.asarray(disc))

def checkDate(d, odate, shipdate):
    return np.logical_and(odate < d, shipdate > d)

def addDate(property, n, dateChar):
    if property == 'YY': # year
        numbers = dateChar.split('-')
        newyear = int(numbers[0]) + n
        return '%d-%s-%s' % (newyear,numbers[1],numbers[2])
    elif property == 'MM': # month
        yy,mm,dd = dateChar.split('-')
        t = int(mm) + n
        if t % 12 == 0: # must be positive
            newm = 12
            newy = int(yy) + t/12 - 1
        else:
            newm = t%12
            newy = int(yy) + t/12
        return '%d-%02d-%s' % (newy,newm,dd)
    elif property == 'DD': # days
        yy,mm,dd = dateChar.split('-')
        x = dt.date(int(yy),int(mm),int(dd)) + dt.timedelta(days=n)
        return '%d-%02d-%02d' % (x.year,x.month,x.day)
    else:
        print 'Support property: %s' % property
        exit(1)

def log(msg):
    os.chdir('/home/sable/hanfeng.c/github/honey/froid')
    logging.basicConfig(filename='froid-example.log', filemode='w', level=logging.DEBUG)
    logging.debug(msg)

def myDate(d):
    return d.strftime("%m/%d/%Y, %H:%M:%S.%f")

def line_count(oprio, mode):
    if mode == 'high':
        return np.logical_or(oprio == '1-URGENT', oprio == '2-HIGH')
    else:
        return np.logical_and(oprio != '1-URGENT', oprio != '2-HIGH')

def line_count_high(oprio):
    return line_count(oprio, 'high')

def line_count_low(oprio):
    return line_count(oprio, 'low')

def q3conditions(cmkt, odate, shipdate):
# isShippedBefore seems unnecessary
    thedate = '1995-03-15'
    return np.logical_and(cmkt == 'BUILDING', checkDate(thedate, odate, shipdate))

def q5conditions(rname, odate):
    beginDatechar = '1994-01-01'
    newDatechar = addDate('YY', 1, beginDatechar)
    return np.logical_and(rname == 'ASIA', np.logical_and(odate >= beginDatechar, odate < newDatechar))

def q6conditions(shipdate, quantity, discount):
    return np.logical_and(np.logical_and(np.logical_and(np.logical_and(shipdate >= '1994-01-01', shipdate < '1995-01-01'), quantity < 24), discount >= 0.05), discount <= 0.07)

def q7conditions(n1name, n2name, shipdate):
    return np.logical_and(np.logical_and(shipdate >= '1995-01-01', shipdate <= '1996-12-31'), np.logical_or(np.logical_and(n1name == 'FRANCE', n2name == 'GERMANY'), np.logical_and(n1name == 'GERMANY', n2name == 'FRANCE')))

def q10conditions(odate, retflag):
    stdatechar = '1993-10-01'
    newstdate = addDate('MM', 3, stdatechar)
    return np.logical_and(retflag == 'R', np.logical_and(odate >= stdatechar, odate < newstdate))

def q12conditions(shipmode, commitdate, receiptdate, shipdate):
    stdatechar = '1994-01-01'
    newstdate = addDate('YY', 1, stdatechar)
    log(newstdate)
    return np.logical_and(
            np.logical_or(shipmode == 'MAIL', shipmode == 'SHIP'),
            np.logical_and(
                np.logical_and(receiptdate >= stdatechar, receiptdate < newstdate),
                np.logical_and(commitdate < receiptdate, shipdate < commitdate)
            )
        )

def q19conditions(pcontainer, lqty, psize, shipmode, shipinst, pbrand):
    def compute(pcontainer, lqty, psize, shipmode, shipinst, pbrand):
        val = False
        if shipmode in ['AIR', 'AIR REG'] and shipinst == 'DELIVER IN PERSON':
            if ( pbrand == 'Brand#12' and
                 pcontainer in ['SM CASE', 'SM BOX', 'SM PACK', 'SM PKG'] and
                 lqty >= 1 and lqty <= 1+10 and
                 psize >= 1 and psize <= 5) :
                val = True
            elif ( pbrand == 'Brand#23' and
                 pcontainer in ['MED CASE', 'MED BOX', 'MED PACK', 'MED PKG'] and
                 lqty >= 10 and lqty <= 10+10 and
                 psize >= 1 and psize <= 10) :
                val = True
            elif ( pbrand == 'Brand#34' and
                 pcontainer in ['LG CASE', 'LG BOX', 'LG PACK', 'LG PKG'] and
                 lqty >= 20 and lqty <= 20+10 and
                 psize >= 1 and psize <= 15) :
                val = True
        return val
    rtn = []
    for id,mod in enumerate(shipmode):
        rtn.append(compute(pcontainer[id], lqty[id], psize[id], mod, shipinst[id], pbrand[id]))
    return rtn




