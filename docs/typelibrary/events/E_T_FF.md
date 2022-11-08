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

mit einem E\_T\_FF lässt sich so ein Blinker realisieren:

mapping:

![](https://user-images.githubusercontent.com/69573151/200581547-83f78279-e1a1-4748-8240-8755630638a9.png)

App:

![](https://user-images.githubusercontent.com/69573151/200581603-62aadee2-2a3a-4562-994f-51475817da3b.png)

EMB\_RES:

![](https://user-images.githubusercontent.com/69573151/200581674-613cabbc-86a6-45b7-ad57-a9c16bd6262d.png)
