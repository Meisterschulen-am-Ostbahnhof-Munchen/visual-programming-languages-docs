# AUS_TO_ALI


![AUS_TO_ALI](./AUS_TO_ALI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AUS_TO_ALI` ist ein zusammengesetzter Baustein (Composite FB), der einen AUS-Adapter (USINT-Werte) in einen ALI-Adapter (LINT-Werte) umwandelt. Er kapselt den Konvertierungsvorgang und stellt eine unidirektionale Schnittstelle zwischen diesen beiden Adaptertypen bereit. Intern wird der Funktionsblock `F_USINT_TO_LINT` aus der IEC 61131-Bibliothek verwendet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine eigenen Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den `AUS_IN`-Adapter (Socket).

### **Ereignis-Ausgänge**
Keine eigenen Ereignis-Ausgänge. Die Ereignisausgabe erfolgt über den `ALI_OUT`-Adapter (Plug).

### **Daten-Eingänge**
Keine eigenen Daten-Eingänge. Die Datenaufnahme erfolgt über den `AUS_IN`-Adapter.

### **Daten-Ausgänge**
Keine eigenen Daten-Ausgänge. Die Datenausgabe erfolgt über den `ALI_OUT`-Adapter.

### **Adapter**
- **AUS_IN** (Socket) – Empfängt einen AUS-Adapter mit unidirektionalem USINT-Datentyp. Enthält:
  - Ereignis-Eingang `E1`
  - Daten-Eingang `D1` (USINT)
- **ALI_OUT** (Plug) – Sendet einen ALI-Adapter mit unidirektionalem LINT-Datentyp. Enthält:
  - Ereignis-Ausgang `E1`
  - Daten-Ausgang `D1` (LINT)

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein Ereignis am `E1`-Eingang des `AUS_IN`-Adapters initiiert die Verarbeitung.
2. Der aktuelle Wert von `AUS_IN.D1` (USINT) wird an den internen Baustein `Convert` (`F_USINT_TO_LINT`) übergeben.
3. Nach der Konvertierung wird das Ergebnis (LINT) über `ALI_OUT.D1` ausgegeben und gleichzeitig ein Ereignis am `E1`-Ausgang des `ALI_OUT`-Adapters gesendet.

Die Typkonvertierung erfolgt gemäß der IEC 61131-Definition von `F_USINT_TO_LINT`: USINT (0..255) wird ohne Vorzeichenverlust in LINT (64-Bit) abgebildet.

## Technische Besonderheiten
- **Composite-Baustein**: Die Konvertierungslogik ist gekapselt und wiederverwendbar.
- **Adapter-basiert**: Die Ein-/Ausgabe erfolgt ausschließlich über Adapter (`AUS` und `ALI`), was die Integration in adapterorientierte Architekturen erleichtert.
- **Unidirektional**: Der Baustein unterstützt nur eine Datenflussrichtung (AUS → ALI).
- **Bibliotheksimport**: Er verwendet den Baustein `iec61131::conversion::F_USINT_TO_LINT` aus der IEC 61131-Bibliothek.
- **Paketstruktur**: Der Baustein ist im Package `adapter::conversion::unidirectional` organisiert.

## Zustandsübersicht
Der `AUS_TO_ALI`-Baustein besitzt keine eigenen Zustandsautomaten. Der interne Ablauf ist rein ereignisgesteuert und zustandslos:
- **Warte**: auf ein Ereignis vom `AUS_IN.E1`
- **Konvertiere**: sofortige Umwandlung des USINT-Werts in LINT
- **Ausgabe**: unverzögertes Senden des Ergebnisses über `ALI_OUT`

Jede Konvertierung ist unabhängig von vorherigen Aufrufen.

## Anwendungsszenarien
- **Schnittstellenanpassung**: Ein System, das Daten als AUS-Adapter (USINT) bereitstellt, muss an einen Empfänger angebunden werden, der einen ALI-Adapter (LINT) erwartet.
- **Datenaufbereitung**: Umwandlung von Sensordaten oder Stellgrößen mit geringer Auflösung (USINT) in einen breiteren Wertebereich (LINT) für weiterführende Berechnungen.
- **Adapter-Kaskadierung**: Als Teil einer Kette von Adapterkonvertierungen, z. B. in einer modularen Steuerungsarchitektur.

## Vergleich mit ähnlichen Bausteinen
- **Direkte Verwendung von `F_USINT_TO_LINT`**: Dieser Baustein arbeitet auf Datenebene ohne Adapter. Der `AUS_TO_ALI` kapselt zusätzlich die Adapterlogik und ist daher besser für adapterbasierte Kommunikation geeignet.
- **Weitere Adapterkonvertierungen**: Für andere Typkombinationen (z. B. `INT_TO_DINT`, `BYTE_TO_WORD`) existieren analoge Composite-Bausteine, die demselben Entwurfsmuster folgen.

## Fazit
Der `AUS_TO_ALI`-Baustein ist eine einfache, aber effektive Lösung zur unidirektionalen Konvertierung zwischen USINT- und LINT-Adaptern. Er erhöht die Wiederverwendbarkeit und Klarheit in Systemen, die auf Adapter-Schnittstellen setzen, und vermeidet die manuelle Verkabelung von Konvertierungslogik.