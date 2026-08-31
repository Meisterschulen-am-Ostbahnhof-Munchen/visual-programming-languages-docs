# ATM_SPLIT_3

![ATM_SPLIT_3](./ATM_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der **ATM_SPLIT_3** ist ein generischer Funktionsbaustein, der einen eingehenden Adapter vom Typ `adapter::types::unidirectional::ATM` auf 3 separate Ausgänge (OUT1, OUT2, OUT3) aufteilt. Er dient zur Weiterleitung eines Zeitsignals an 3 nachfolgende Bausteine, ohne die Daten zu verändern. Der Baustein ist als generischer Typ (`GEN_ATM_SPLIT`) implementiert und wird zur Laufzeit parametrisiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::ATM` | IN | Socket | Eingangssignal (ATM) |
| `adapter::types::unidirectional::ATM` | OUT1 | Plug | Ausgang 1 (identisch zu IN) |
| `adapter::types::unidirectional::ATM` | OUT2 | Plug | Ausgang 2 (identisch zu IN) |
| `adapter::types::unidirectional::ATM` | OUT3 | Plug | Ausgang 3 (identisch zu IN) |

## Funktionsweise

Der Baustein leitet das am Socket **IN** anliegende ATM-Signal unverändert auf alle 3 Plugs (OUT1, OUT2, OUT3) weiter. Es findet keine Datenmanipulation, Filterung oder Verzögerung statt. Die Aufteilung erfolgt rein strukturell: Jeder Ausgang erhält eine eigene Kopie der Referenz auf den zugrundeliegenden Zeitwert.

## Technische Besonderheiten

- **Generische Implementierung**: Der FB verwendet das Generic-Class-Name-Attribut (`eclipse4diac::core::GenericClassName`) mit dem Wert `'GEN_ATM_SPLIT'`, sodass dieselbe Klasse über den GenericClassName-Mechanismus die Aritäten `ATM_SPLIT_2`, `ATM_SPLIT_3` und `ATM_SPLIT_4` abdeckt.
- **Unidirektionale Adapter**: Alle Adapter sind vom Typ `adapter::types::unidirectional::ATM` (nur Vorwärtsrichtung).
- **Keine Zustandsautomatik**: Der Baustein besitzt keinen expliziten ECC (Execution Control Chart); die Weiterleitung erfolgt direkt und ereignisunabhängig.

## Zustandsübersicht

Der Baustein implementiert keine Zustandsautomaten. Die Funktionalität beschränkt sich auf die passive Weiterleitung des Eingangssignals an alle 3 Ausgänge. Eine Zustandsvisualisierung ist daher nicht erforderlich.

## Anwendungsszenarien

- **Signalverteilung**: Aufteilung eines ATM-basierten Zeitsignals (z. B. einer Verzögerungsdauer) an mehrere parallel arbeitende Steuerungskomponenten.
- **Redundanz**: Bereitstellung desselben Zeitwerts für ein primäres und ein redundantes System.
- **Debugging**: Anschluss eines Analyse- oder Logging-Bausteins parallel zum bestehenden Pfad, ohne die Originalsignalkette zu unterbrechen.

## Vergleich mit ähnlichen Bausteinen

Ähnliche Funktionalität bieten die weiteren Aritäten `ATM_SPLIT_2`/`ATM_SPLIT_3`/`ATM_SPLIT_4` sowie der strukturell identische `AR_SPLIT_3` für den Datentyp `REAL`. Die Auswahl der Arität hängt von der benötigten Anzahl an Ausgängen ab.

- **[`ATM_SPLIT_3_UNGATED`](ATM_SPLIT_3_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Jeder Ausgangs-Plug wird unabhängig aktualisiert: Der eingehende Wert wird nur dann auf einen Ausgang geschrieben und dessen Adapter-Event gesendet, wenn er sich vom aktuellen Wert dieses Ausgangs unterscheidet. Bereits synchrone Ausgänge bleiben still, während ein gerade erst verbundener (oder nicht mehr synchroner) Ausgang weiterhin die nötige Aktualisierung erhält.

## Fazit

Der **ATM_SPLIT_3** ist ein einfacher, aber essenzieller Baustein zur Vervielfachung eines Zeitsignals in IEC 61499-basierten Steuerungssystemen. Seine generische Auslegung und die klare Schnittstelle machen ihn zur ersten Wahl, wenn ein Zeitwert an mehrere unabhängige Zielbausteine weitergegeben werden muss.
