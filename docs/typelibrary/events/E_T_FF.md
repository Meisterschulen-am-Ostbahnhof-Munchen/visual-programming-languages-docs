### E\_T\_FF

Toggle flip flop

IEC 61499-1 Annex A

![](https://user-images.githubusercontent.com/69573151/200578501-6ff6cc82-30c8-40a2-9a74-17fd320520ea.png)

*   Input
    *   CLK Clock for triggering a output toggle
*   Output
    *   EO inform of toggled output
    *   Q value of flip flop

das Toggle flip flop stellt einen "Stromstoßschalter" dar. 

[https://de.wikipedia.org/wiki/Stromsto%C3%9Fschalter](https://de.wikipedia.org/wiki/Stromsto%C3%9Fschalter)

#### E\_T\_FF Anwendungen

##### E\_T\_FF Anwendungen Taster

mit einem E\_T\_FF lässt sich so ein Taster realisieren, der eine Lampe ein und ausschaltet:

mapping:

![](https://user-images.githubusercontent.com/69573151/200582493-3b7830e9-6c99-48c8-8edb-3c51c2ec61f1.png)

App:

![](https://user-images.githubusercontent.com/69573151/200582537-03463197-4460-447e-b246-f11bafed81d3.png)

EMB\_RES:

![](https://user-images.githubusercontent.com/69573151/200582652-15139148-a200-49fb-a683-93e341eab607.png)

##### E\_T\_FF Anwendungen Blinker

mit einem E\_T\_FF lässt sich so ein Blinker realisieren:

mapping:

![](https://user-images.githubusercontent.com/69573151/200581547-83f78279-e1a1-4748-8240-8755630638a9.png)

App:

![](https://user-images.githubusercontent.com/69573151/200581603-62aadee2-2a3a-4562-994f-51475817da3b.png)

EMB\_RES:

![](https://user-images.githubusercontent.com/69573151/200581674-613cabbc-86a6-45b7-ad57-a9c16bd6262d.png)




Siehe auch: [https://www.holobloc.com/doc/fb/rt/events/E_T_FF.htm](https://www.holobloc.com/doc/fb/rt/events/E_T_FF.htm)
