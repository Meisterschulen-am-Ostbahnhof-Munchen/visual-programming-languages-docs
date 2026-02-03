# logiBUS_DI_Events_S

```{index} single: logiBUS_DI_Events_S
```

* * * * * * * * * *
## Einleitung
Der Strukturdatentyp `logiBUS_DI_Events_S` dient der Konfiguration von Ereignissen für digitale Eingänge (DI) innerhalb des logiBUS-Frameworks. Er definiert den Ereignistyp, der einem bestimmten digitalen Eingangskanal zugeordnet werden kann. Dieser Datentyp ist ein wesentlicher Bestandteil für die Parametrierung von logiBUS-E/A-Funktionsblöcken.

## Schnittstellenstruktur
Dieser Baustein ist ein reiner Datentyp (Structured Type) und besitzt keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne eines Funktionsbausteins. Seine Struktur wird als Eingangs- oder Ausgangsdatenparameter in anderen Funktionsblöcken verwendet.

### **Daten-Eingänge**
Nicht zutreffend – Dies ist ein Datentyp.

### **Daten-Ausgänge**
Nicht zutreffend – Dies ist ein Datentyp.

### **Adapter**
Nicht zutreffend – Dies ist ein Datentyp.

## Funktionsweise
Der Datentyp `logiBUS_DI_Events_S` kapselt eine einzelne Variable (`EType`), die einen Ereignistyp-Code repräsentiert. Der Standardwert ist auf `255` gesetzt, was typischerweise einem inaktiven oder nicht konfigurierten Zustand entspricht. Konkrete Werte (z.B. 0, 1, 2, ...) werden verwendet, um bestimmte Ereignisse (wie Flankenwechsel) zu identifizieren, die dann von übergeordneten Steuerungslogiken verarbeitet werden können.

## Technische Besonderheiten
*   **Datentyp:** Es handelt sich um einen strukturierten Datentyp (`STRUCT`), der in anderen Funktionsblöcken als komplexer Datenparameter genutzt wird.
*   **Initialwert:** Die enthaltene Variable `EType` ist mit dem Wert `255` vorinitialisiert. Dieser Wert dient wahrscheinlich als Platzhalter oder "ungültig"-Kennung.
*   **Basistyp:** Die Variable `EType` ist vom Typ `USINT` (Unsigned Short Integer, 0-255), was einen begrenzten und effizienten Wertebereich für Ereigniscodes bietet.

## Zustandsübersicht
Da es sich um einen passiven Datentyp handelt, existiert keine Zustandsmaschine. Der "Zustand" ist der gespeicherte Wert der Variable `EType`.

## Anwendungsszenarien
Dieser Strukturdatentyp wird primär in Verbindung mit logiBUS-I/O-Funktionsblöcken verwendet, beispielsweise:
*   Als Element in einem Array zur Konfiguration aller digitalen Eingänge eines Moduls.
*   Als Parameter, um festzulegen, bei welchem physikalischen Ereignis (z.B. steigende Flanke) ein logisches Event im Steuerungsprogramm ausgelöst werden soll.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsbausteinen (FBs) wie `E_R_TRIG` oder `F_TRIG`, die selbstständig Flankenereignisse generieren, ist `logiBUS_DI_Events_S` ein reiner Konfigurationsdatentyp. Er stellt die Information bereit, *welches* Hardware-Ereignis von einem separaten Treiber- oder Hardwareabstraktionsbaustein in ein solches logisches Flankenereignis übersetzt werden soll.

## Fazit
Der `logiBUS_DI_Events_S` ist ein grundlegender Konfigurationsbaustein innerhalb der logiBUS-Architektur. Er ermöglicht eine flexible und parametrierbare Zuordnung von Hardware-Ereignissen an digitalen Eingängen zu software-seitigen Verarbeitungsroutinen. Seine einfache, auf einen `USINT` reduzierte Struktur gewährleistet Effizienz und einfache Handhabung in übergeordneten Konfigurationsstrukturen.