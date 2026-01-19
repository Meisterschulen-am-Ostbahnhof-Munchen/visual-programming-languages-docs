# E_SPLIT_4

```{index} single: E_SPLIT_4
```

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->

* * * * * * * * * *

## Einleitung
Der `E_SPLIT_4` ist ein grundlegender Funktionsbaustein nach IEC 61499, der ein einzelnes Eingangereignis (`EI`) in eine Sequenz von vier Ausgangsereignissen (`EO1` bis `EO4`) aufteilt.

## Schnittstellenstruktur

### **Ereignis-Eingang**
- **EI**: Das Eingangereignis, das die Sequenz auslöst.

### **Ereignis-Ausgänge**
- **EO1**: Das erste Ausgangsereignis der Sequenz.
- **EO2**: Das zweite Ausgangsereignis der Sequenz.
- **EO3**: Das dritte Ausgangsereignis der Sequenz.
- **EO4**: Das vierte Ausgangsereignis der Sequenz.

## Funktionsweise
Wenn ein Ereignis am Eingang `EI` eintrifft, löst der Baustein sofort nacheinander die vier Ausgangsereignisse aus. Die Reihenfolge ist dabei garantiert:
1.  Zuerst wird `EO1` ausgelöst.
2.  Unmittelbar danach wird `EO2` ausgelöst.
3.  Unmittelbar danach wird `EO3` ausgelöst.
4.  Unmittelbar danach wird `EO4` ausgelöst.

## Technische Besonderheiten
- **1-zu-4 Sequenz**: Teilt ein Ereignis in eine garantierte Sequenz von vier Ereignissen auf.
- **Zustandslos**: Der Baustein hat keinen internen Speicher, der über eine einzelne Transaktion hinausgeht.
- **Generischer Baustein**: Die Funktionalität wird durch die generische Klasse `GEN_E_SPLIT` zur Verfügung gestellt.

## Anwendungsszenarien
- **Komplexe Initialisierung**: Ein `INIT`-Ereignis kann genutzt werden, um nacheinander vier verschiedene Systemkomponenten zu initialisieren.
- **Ablaufsteuerung**: Anstoßen von vier aufeinanderfolgenden Aktionen mit einem einzigen Trigger-Ereignis.

## Fazit
Der `E_SPLIT_4`-Baustein ist ein nützliches Werkzeug, um aus einem einzelnen Trigger eine feste, kurze Ereignissequenz von vier Schritten zu generieren. Seine Einfachheit und die garantierte Ausführungsreihenfolge machen ihn zu einer robusten Komponente für die Ablaufsteuerung in IEC 61499-Anwendungen.