# E\_T\_FF

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

## E\_T\_FF Anwendungen

### E\_T\_FF Anwendungen Taster

mit einem E\_T\_FF lässt sich so ein Taster realisieren, der eine Lampe ein und ausschaltet:

mapping:

![](https://user-images.githubusercontent.com/69573151/200582493-3b7830e9-6c99-48c8-8edb-3c51c2ec61f1.png)

App:

![](https://user-images.githubusercontent.com/69573151/200582537-03463197-4460-447e-b246-f11bafed81d3.png)

EMB\_RES:

![](https://user-images.githubusercontent.com/69573151/200582652-15139148-a200-49fb-a683-93e341eab607.png)

### E\_T\_FF Anwendungen Blinker

mit einem E\_T\_FF lässt sich so ein Blinker realisieren:

mapping:

![](https://user-images.githubusercontent.com/69573151/200581547-83f78279-e1a1-4748-8240-8755630638a9.png)

App:

![](https://user-images.githubusercontent.com/69573151/200581603-62aadee2-2a3a-4562-994f-51475817da3b.png)

EMB\_RES:

![](https://user-images.githubusercontent.com/69573151/200581674-613cabbc-86a6-45b7-ad57-a9c16bd6262d.png)




* * * * * * * * * *

Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)


**Der Baustein E_T_FF in der IEC 61499: Eine korrigierte Einführung**

Die IEC 61499 ist ein internationaler Standard, der sich mit der Funktionsbausteinmodellierung für industrielle Automatisierungssysteme beschäftigt. Sie bietet einen Rahmen für die Entwicklung von verteilten Steuerungssystemen, die flexibel, modular und wiederverwendbar sind. Ein zentrales Element in diesem Standard sind die Funktionsbausteine, die als grundlegende Komponenten für die Implementierung von Steuerungslogik dienen. Einer dieser Bausteine ist der E_T_FF (Event-Triggered Flip-Flop), der in diesem Aufsatz näher betrachtet werden soll.

## 1. Grundlagen des E_T_FF

Der E_T_FF ist ein ereignisgesteuerter Flip-Flop-Baustein, der in der IEC 61499 verwendet wird, um Zustandsänderungen in einem System zu verwalten. Ein Flip-Flop ist ein grundlegendes Element der digitalen Logik, das zwei stabile Zustände hat und als Speicherbaustein verwendet werden kann. Der E_T_FF erweitert dieses Konzept um die ereignisgesteuerte Funktionalität, die in der IEC 61499 von zentraler Bedeutung ist.

## 2. Funktionsweise des E_T_FF

Der E_T_FF hat einen Ereigniseingang (CLK), der eine Zustandsänderung auslöst. Der Baustein hat zwei Ausgänge: einen Datenausgang (Q) vom Typ BOOL und einen Ereignisausgang (EO). Der Datenausgang gibt den aktuellen Zustand des Flip-Flops wieder, während der Ereignisausgang ein Ereignis signalisiert, wenn sich der Zustand ändert.

Die Funktionsweise des E_T_FF kann wie folgt beschrieben werden:

- **Ereignisgesteuerte Zustandsänderung:** Wenn ein Ereignis am Ereigniseingang (CLK) eintrifft, wird der Zustand des Flip-Flops umgeschaltet. Der aktuelle Zustand wird am Datenausgang (Q) ausgegeben. Wenn der Zustand des Flip-Flops von FALSE auf TRUE oder von TRUE auf FALSE wechselt, wird ein Ereignis am Ereignisausgang (EO) ausgelöst.

- **Zustandsspeicherung:** Der E_T_FF speichert den aktuellen Zustand, bis ein neues Ereignis am Ereigniseingang eintrifft. Dies ermöglicht die Verwendung des Bausteins als Speicherelement in einer Steuerungslogik.

- **Ereignisausgang:** Wenn sich der Zustand des Flip-Flops ändert, wird ein Ereignis am Ereignisausgang (EO) ausgelöst. Dieses Ereignis kann verwendet werden, um nachgelagerte Bausteine zu aktivieren oder andere Aktionen im System auszulösen.

## 3. Anwendungsbeispiele

Der E_T_FF kann in verschiedenen Anwendungen eingesetzt werden, bei denen es darum geht, Zustände zu speichern und ereignisgesteuert zu ändern. Einige Beispiele sind:

- **Zustandsmaschinen:** In Zustandsmaschinen kann der E_T_FF verwendet werden, um den aktuellen Zustand der Maschine zu speichern und bei Bedarf zu ändern. Jeder Zustand kann durch einen E_T_FF repräsentiert werden, und die Übergänge zwischen den Zuständen können durch Ereignisse gesteuert werden.

- **Speicherung von Schaltzuständen:** In Steuerungssystemen, bei denen Schaltzustände (z.B. Ein/Aus) gespeichert werden müssen, kann der E_T_FF als Speicherelement verwendet werden. Der Zustand des Flip-Flops kann durch ein Ereignis geändert werden, das z.B. durch einen Taster oder einen Sensor ausgelöst wird.

- **Synchronisation von Prozessen:** Der E_T_FF kann auch zur Synchronisation von Prozessen verwendet werden. Wenn ein Prozess einen bestimmten Zustand erreicht hat, kann ein Ereignis ausgelöst werden, das andere Prozesse aktiviert oder deaktiviert.

## 4. Vorteile des E_T_FF in der IEC 61499

Die Verwendung des E_T_FF in der IEC 61499 bietet mehrere Vorteile:

- **Ereignisgesteuerte Architektur:** Die ereignisgesteuerte Architektur der IEC 61499 ermöglicht eine effiziente und flexible Steuerungslogik. Der E_T_FF passt perfekt in dieses Konzept, da er Zustandsänderungen basierend auf Ereignissen verwaltet.

- **Modularität und Wiederverwendbarkeit:** Wie alle Bausteine in der IEC 61499 ist der E_T_FF modular und wiederverwendbar. Er kann in verschiedenen Anwendungen und Systemen eingesetzt werden, ohne dass Änderungen am Baustein selbst vorgenommen werden müssen.

- **Einfache Integration:** Der E_T_FF kann einfach in bestehende Steuerungslogiken integriert werden. Durch die klare Trennung von Ereignis- und Datenfluss ist die Integration in komplexe Systeme unkompliziert.

## 5. Fazit

Der E_T_FF ist ein wichtiger Baustein in der IEC 61499, der es ermöglicht, Zustände in einer ereignisgesteuerten Architektur zu speichern und zu verwalten. Seine einfache Funktionsweise und die klare Trennung von Ereignis- und Datenfluss machen ihn zu einem vielseitigen Werkzeug in der industriellen Automatisierung. Durch die Verwendung des E_T_FF können Entwickler flexible, modulare und wiederverwendbare Steuerungssysteme erstellen, die den Anforderungen moderner Automatisierungsanwendungen gerecht werden.

Die IEC 61499 und Bausteine wie der E_T_FF tragen dazu bei, die Komplexität von Steuerungssystemen zu reduzieren und gleichzeitig die Flexibilität und Effizienz zu erhöhen. In einer zunehmend vernetzten und automatisierten Welt sind solche Standards und Bausteine unverzichtbar, um die Herausforderungen der Industrie 4.0 zu meistern.





Siehe auch: [https://www.holobloc.com/doc/fb/rt/events/E_T_FF.htm](https://www.holobloc.com/doc/fb/rt/events/E_T_FF.htm)
