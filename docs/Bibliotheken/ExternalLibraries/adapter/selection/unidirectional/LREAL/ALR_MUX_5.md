# ALR_MUX_5


![ALR_MUX_5](./ALR_MUX_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALR_MUX_5** ist ein generischer Multiplexer für den Adaptertyp `adapter::types::unidirectional::ALR`. Er wählt aus fünf Eingangsadaptern (IN1 bis IN5) einen aus und leitet dessen Werte über den Ausgangsadapter OUT weiter. Die Auswahl erfolgt über den Index K (ganzzahliger Wert von 0 bis 4). Der FB wird über den Ereigniseingang REQ gesteuert und bestätigt die Ausführung mit dem Ausgang CNF.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Setzt den Index K und übernimmt die Auswahl |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der Ausführung nach REQ |

### **Daten-Eingänge**
| Name | Typ | Wertebereich | Kommentar |
|------|-----|--------------|-----------|
| K    | UINT | 0 .. 4       | Index des auszuwählenden Eingangs |

### **Daten-Ausgänge**
(Keine direkten Datenausgänge vorhanden – die Datenübertragung erfolgt über den Adapter OUT.)

### **Adapter**

**Sockets (Eingänge)**
| Name | Typ | Kommentar |
|------|-----|-----------|
| IN1  | adapter::types::unidirectional::ALR | Eingangswert 1 (K = 0) |
| IN2  | adapter::types::unidirectional::ALR | Eingangswert 2 (K = 1) |
| IN3  | adapter::types::unidirectional::ALR | Eingangswert 3 (K = 2) |
| IN4  | adapter::types::unidirectional::ALR | Eingangswert 4 (K = 3) |
| IN5  | adapter::types::unidirectional::ALR | Eingangswert 5 (K = 4) |

**Plug (Ausgang)**
| Name | Typ | Kommentar |
|------|-----|-----------|
| OUT  | adapter::types::unidirectional::ALR | Ausgang: liefert den ausgewählten Eingangswert |

## Funktionsweise

1. Der FB erwartet ein Ereignis am Eingang **REQ**. Gleichzeitig muss der Index **K** einen gültigen Wert zwischen 0 und 4 enthalten.
2. Beim Empfang von REQ wird der Adapter **IN(K+1)** ausgewählt und dessen Daten über **OUT** bereitgestellt.
3. Nach erfolgreicher Auswahl wird das Ereignis **CNF** gesendet, um die Übernahme zu bestätigen.
4. Wird ein ungültiger Index (K > 4) gesetzt, ist das Verhalten undefiniert; der FB sollte im Anwendungskontext mit einer Bereichsprüfung abgesichert werden.

Die Datenübertragung erfolgt **unidirektional** vom Eingang zum Ausgang. Der FB ist generisch implementiert und kann für jeden Adapter des Typs `adapter::types::unidirectional::ALR` verwendet werden, unabhängig von den konkreten Inhalten der Adapter-Schnittstelle.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generische Klasse (`GEN_ALR_MUX`) deklariert und kann durch Typisierung an verschiedene ALR-Adapter angepasst werden.
- **Adapter-basiert**: Alle Ein- und Ausgänge sind Adapter vom gleichen, unidirektionalen Typ. Dies erlaubt eine flexible Kopplung mit anderen Bausteinen, die denselben Adapter bereitstellen.
- **Keine internen Zustände** außer der Bereitschaft auf REQ – der FB arbeitet rein kombinatorisch bei jedem Ereignis.
- **5 Eingänge** fest codiert; eine Erweiterung auf andere Anzahlen erfordert eine neue Variante des FBs.

## Zustandsübersicht

Der FB besitzt keine explizite Zustandsmaschine. Er verharrt im **IDLE**-Zustand, bis ein REQ eintrifft. Bei REQ wird die Auswahl durchgeführt und sofort CNF gesendet. Es gibt keine wartenden oder blockierenden Zustände.

| Zustand | Beschreibung |
|---------|--------------|
| IDLE    | Warten auf REQ |

## Anwendungsszenarien

- **Signalumschaltung** in der Automatisierungstechnik: z. B. Auswahl eines von fünf Sensordatenströmen (ALR-Format) für die Weiterverarbeitung.
- **Test- und Simulationsumgebungen**: Umschalten zwischen verschiedenen Testquellen ohne Neuverkabelung.
- **Multiplexen von ALR-Adapterdaten** in einer zentralen Steuerung, bei der je nach Betriebsart unterschiedliche Datenquellen aktiviert werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Eingänge | Auswahlsteuerung | Bemerkung |
|----------|-----|----------|------------------|-----------|
| ALR_MUX_5 | Adapter (ALR) | 5 | K (UINT) über REQ | Speziell für ALR-Adapter, generisch |
| Standard-MUX (z. B. MUX_INT) | elementar (z. B. INT) | variabel | K über REQ | Arbeitet mit einfachen Datentypen, nicht generisch über Adapter |
| MUX_E_4 | Adapter (beliebig) | 4 | K (BOOL) | Meist feste Anzahl, kein generischer Adapter |

Der ALR_MUX_5 zeichnet sich durch die Adapter-Schnittstelle aus, die komplexe zusammengesetzte Datenstrukturen transportieren kann, und durch die generische Auslegung.

## Fazit

Der Funktionsblock **ALR_MUX_5** bietet eine saubere, ereignisgesteuerte Multiplex-Funktionalität für fünf unidirektionale ALR-Adapter. Er ist generisch, einfach einsetzbar und eignet sich für alle Anwendungen, die eine dynamische Auswahl aus mehreren Datenquellen im ALR-Format erfordern. Dank der Adaptertechnik können auch komplexe Datenpakete ohne zusätzlichen Aufwand umgeschaltet werden.