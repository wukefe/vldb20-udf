import numpy as np

def discount_price(extprice, disc):
    return extprice * (1 - disc)

def promo_disc(ptype, extprice, disc):
    val = []
    for id,typ in enumerate(ptype):
        if typ.startswith('PROMO'):   # ptype like 'PROMO%'
            val.append(discount_price(extprice[id], disc[id]))
        else:
            val.append(0)
    return val

def demo():
    ptype = ["PROMOnice", "Dummyhello", "PROMOcool"]
    extprice = [1.2, 1.3, 1.5]
    disc = [0.3, 0.4, 0.5]
    print promo_disc(np.asarray(ptype), np.asarray(extprice), np.asarray(disc))


