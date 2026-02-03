# F_DINT_TO_LINT

```{index} single: F_DINT_TO_LINT
```

<img width="1434" height="212" alt="F_DINT_TO_LINT" src="https://github.com/user-attachments/assets/cf39f6ad-2d08-456e-ae6b-1a02e87a6f50" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_LINT` dient der Konvertierung eines 32-Bit Ganzzahlwerts (DINT) in einen 64-Bit Ganzzahlwert (LINT). Dieser Baustein ist besonders nützlich in Szenarien, bei denen eine Erweiterung des Wertebereichs oder eine Typanpassung für nachfolgende Verarbeitungsschritte erforderlich ist.

![F_DINT_TO_LINT](F_DINT_TO_LINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den erfolgreichen Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (DINT): Der 32-Bit Ganzzahlwert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (LINT): Der resultierende 64-Bit Ganzzahlwert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Wert des `IN`-Eingangs in den `OUT`-Ausgang kopiert. Dabei erfolgt eine automatische Typumwandlung von DINT zu LINT, wobei der numerische Wert erhalten bleibt.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne Datenverlust, da der LINT-Typ einen größeren Wertebereich als DINT unterstützt.
- Der Algorithmus ist in Structured Text (ST) implementiert und besteht aus einer einfachen Zuweisung.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Erweiterung des Wertebereichs für nachfolgende Berechnungen
- Typanpassung in heterogenen Systemen
- Datenaufbereitung für Schnittstellen mit unterschiedlichen Anforderungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen Konvertierungsbausteinen bietet `F_DINT_TO_LINT` eine spezialisierte und typsichere Lösung für die spezifische Konvertierung zwischen DINT und LINT. Andere Bausteine könnten allgemeinere Konvertierungsmöglichkeiten bieten, sind aber möglicherweise weniger effizient oder erfordern zusätzliche Konfiguration.

## Fazit
Der `F_DINT_TO_LINT` Funktionsblock stellt eine einfache und effiziente Lösung für die Konvertierung von 32-Bit zu 64-Bit Ganzzahlen dar. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einem zuverlässigen Baustein in Steuerungssystemen, wo solche Typkonvertierungen benötigt werden.