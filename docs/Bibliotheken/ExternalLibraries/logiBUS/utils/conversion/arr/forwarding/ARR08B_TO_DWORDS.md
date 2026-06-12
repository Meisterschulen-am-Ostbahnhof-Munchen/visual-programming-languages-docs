# ARR08B_TO_DWORDS

Dieser Funktionsbaustein konvertiert ein Byte-Array der Länge 8 (8 Bytes) in zwei 32‑Bit-Datenwörter (DWORDs). Er dient zur Aufteilung eines zusammenhängenden 8‑Byte-Datenblocks in zwei 4‑Byte große Integer‑Werte.


![ARR08B_TO_DWORDS](./ARR08B_TO_DWORDS.svg)

* * * * * * * * * *
## Einleitung

Der **ARR08B_TO_DWORDS** ist ein reiner Konvertierungsbaustein, der aus einem eingehenden 8‑Byte-Array zwei separate DWORD-Werte erzeugt. Die Umwandlung erfolgt byteweise, wobei die ersten vier Bytes dem ersten Ausgang (OUT_00) und die letzten vier Bytes dem zweiten Ausgang (OUT_01) zugeordnet werden. Der Baustein wird über ein Ereignis (REQ) angestoßen und gibt nach Abschluss der Konvertierung ein Bestätigungsereignis (CNF) aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mitgeführte Daten |
|----------|--------------|-------------------|
| **REQ**   | Startet die Konvertierung des Eingangsarrays. | IN (8‑Byte‑Array) |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mitgeführte Daten |
|----------|--------------|-------------------|
| **CNF**   | Bestätigt die abgeschlossene Konvertierung. | OUT_00, OUT_01 |

### **Daten-Eingänge**

| Name | Datentyp | Array-Dimension | Beschreibung |
|------|----------|-----------------|--------------|
| **IN** | BYTE     | [0..7]          | 8‑Byte‑Eingangsarray, das in zwei DWORDs zerlegt wird. |

### **Daten-Ausgänge**

| Name    | Datentyp | Beschreibung |
|---------|----------|--------------|
| **OUT_00** | DWORD    | Erster DWORD (Bytes 0–3 des Arrays). |
| **OUT_01** | DWORD    | Zweiter DWORD (Bytes 4–7 des Arrays). |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Der Baustein führt eine direkte byteweise Kopie aus dem Eingangsarray in die Ausgangsvariablen durch:

1. Die Bytes **IN[0]** bis **IN[3]** werden den niederwertigsten bis höherwertigsten Bytes von **OUT_00** zugewiesen.
2. Die Bytes **IN[4]** bis **IN[7]** werden entsprechend **OUT_01** zugeordnet.

Die Zuweisung erfolgt im Structured‑Text‑Rumpf:

```
OUT_00.%B0 := IN[0];
OUT_00.%B1 := IN[1];
OUT_00.%B2 := IN[2];
OUT_00.%B3 := IN[3];
OUT_01.%B0 := IN[4];
OUT_01.%B1 := IN[5];
OUT_01.%B2 := IN[6];
OUT_01.%B3 := IN[7];
```

Der Baustein arbeitet ohne Verzögerung oder Zustandsspeicher; die Ausgänge werden unmittelbar nach dem Eintreffen des REQ-Ereignisses aktualisiert und das CNF-Ereignis wird sofort ausgelöst.

## Technische Besonderheiten

- **Endianness**: Der Baustein interpretiert das Array im *Little‑Endian*-Format – das erste Byte (Index 0) wird dem niederwertigsten Byte des DWORD zugeordnet. Diese Annahme ist typisch für viele industrielle Protokolle und Systeme.
- **Keine Prüfung der Array-Länge**: Das Array wird als genau 8 Byte vorausgesetzt. Eine abweichende Eingangsgröße würde zu undefiniertem Verhalten führen.
- **Funktionaler Baustein**: Der FB ist rein funktional und besitzt keine internen Zustände.

## Zustandsübersicht

Der Baustein hat keinen internen Zustandsautomaten. Er arbeitet ereignisgesteuert und gibt nach jeder Aktivierung sofort das CNF-Signal zurück. Die Ausgänge bleiben bis zur nächsten REQ-Aktivierung erhalten.

## Anwendungsszenarien

- **Datenpaket-Zerlegung**: Trennung eines 8‑Byte‑Telegramms in zwei 32‑Bit‑Werte, z. B. bei der Kommunikation mit industriellen Feldgeräten (CANopen, Modbus, etc.).
- **Sensorwertverarbeitung**: Aufteilung eines 8‑Byte‑Rohdatenblocks von Sensoren, die zwei physikalische Messwerte (je 4 Byte) liefern.
- **Konvertierung in der logiBUS-Umgebung**: Innerhalb des Pakets `logiBUS::utils::conversion::arr::forwarding` als Standardbaustein zur Vorwärtskonvertierung von Array-Daten.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| **BYTE_TO_DWORD** | Einzeln konvertiert ein BYTE-Array von 4 Bytes in ein DWORD. | Benötigt separate Aufrufe für jedes 4‑Byte‑Segment. |
| **ARR08B_TO_DWORDS** | Konvertiert ein 8‑Byte-Array auf einmal in zwei DWORDs. | Integrierte Aufteilung in nur einem Schritt, reduziert Aufrufanzahl und Code. |

Der vorliegende Baustein bietet somit eine kompaktere Lösung als die Kombination mehrerer elementarer Konvertierungsbausteine.

## Fazit

Der **ARR08B_TO_DWORDS** ist ein einfacher, aber nützlicher Funktionsbaustein zur schnellen und direkten Zerlegung eines 8‑Byte‑Arrays in zwei DWORDs. Dank seiner klaren Byte‑zu‑Byte‑Zuordnung und der Ereignissteuerung lässt er sich gut in datenflussorientierte Steuerungsanwendungen integrieren. Die Verwendung setzt ein Little‑Endian‑Format voraus; für andere Endianness‑Anforderungen sind Anpassungen erforderlich. Insgesamt ist der Baustein eine effiziente Lösung für die Vorverarbeitung binärer Daten.