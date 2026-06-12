# ALI_TO_AB


![ALI_TO_AB](./ALI_TO_AB.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALI_TO_AB** ist ein zusammengesetzter Baustein (Composite FB) gemäß IEC 61499-2, der zur Umwandlung eines LINT‑Werts (64‑Bit Ganzzahl) in einen BYTE‑Wert (8‑Bit) dient. Die Konvertierung erfolgt über zwei unidirektionale Adapter‑Schnittstellen: Der ALI_Empfänger (Socket) nimmt einen LINT‑Wert entgegen, und der AB_Sender (Plug) gibt den konvertierten BYTE‑Wert weiter. Intern wird der Konvertierungsbaustein `F_LINT_TO_BYTE` aus der IEC 61131‑Bibliothek verwendet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Ereignisse werden ausschließlich über den Adapter **ALI_IN** (Socket) empfangen.

| Ereignis | Beschreibung |
|----------|--------------|
| *E1 (über ALI_IN)* | Signal zur Auslösung der Konvertierung. |

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignis-Ausgänge. Ereignisse werden ausschließlich über den Adapter **AB_OUT** (Plug) gesendet.

| Ereignis | Beschreibung |
|----------|--------------|
| *E1 (über AB_OUT)* | Quittung nach erfolgreicher Konvertierung. |

### **Daten-Eingänge**

Der FB besitzt keine direkten Daten-Eingänge. Daten werden ausschließlich über den Adapter **ALI_IN** (Socket) bereitgestellt.

| Daten | Typ | Beschreibung |
|-------|-----|--------------|
| *D1 (über ALI_IN)* | LINT | 64‑Bit Ganzzahl, die konvertiert werden soll. |

### **Daten-Ausgänge**

Der FB besitzt keine direkten Daten-Ausgänge. Daten werden ausschließlich über den Adapter **AB_OUT** (Plug) ausgegeben.

| Daten | Typ | Beschreibung |
|-------|-----|--------------|
| *D1 (über AB_OUT)* | BYTE | 8‑Bit konvertierter Wert. |

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **ALI_IN** | Socket (Eingang) | `adapter::types::unidirectional::ALI` | Nimmt den LINT‑Wert sowie ein zugehöriges Ereignis entgegen. |
| **AB_OUT** | Plug (Ausgang) | `adapter::types::unidirectional::AB` | Gibt den konvertierten BYTE‑Wert sowie ein Quittungsereignis aus. |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis am **ALI_IN**‑Adapter (E1).
2. Sobald das Ereignis eintrifft, wird der Datenwert D1 (LINT) an den internen Konvertierungsbaustein `F_LINT_TO_BYTE` übergeben und dort in einen BYTE‑Wert umgewandelt.
3. Nach Abschluss der Konvertierung wird der BYTE‑Wert über den **AB_OUT**‑Adapter (D1) ausgegeben und das Quittungsereignis (E1) gesendet.

Die Umwandlung von LINT (64 Bit) nach BYTE (8 Bit) erfolgt durch Abschneiden der niederwertigsten 8 Bits. Höherwertige Bits gehen dabei verloren.

## Technische Besonderheiten

- **Typkonvertierung mit Werteverlust:** Da LINT 64 Bit breit ist, BYTE jedoch nur 8 Bit, werden nur die unteren 8 Bit des LINT-Werts übernommen. Ein Wertebereich von 0 … 255 wird korrekt abgebildet; größere Zahlen werden modulo 256 reduziert.
- **Reine Adapter-Schnittstelle:** Der Baustein besitzt keine direkten Ein‑/Ausgänge, sondern kommuniziert ausschließlich über zwei unidirektionale Adapter. Dies ermöglicht eine lose Kopplung in adapterbasierten Architekturen.
- **Standardkonformität:** Der FB setzt auf den IEC 61131‑Baustein `F_LINT_TO_BYTE` auf und ist daher in Umgebungen einsetzbar, die diese Bibliothek unterstützen.

## Zustandsübersicht

Als zusammengesetzter Baustein besitzt **ALI_TO_AB** keinen eigenen internen Zustandsautomaten. Die Zustände des enthaltenen `F_LINT_TO_BYTE` (z. B. IDLE, BUSY) sind für den Anwender nicht sichtbar. Der FB verhält sich daher wie eine kombinatorische oder ereignisgesteuerte Funktion ohne explizite Zustandsmaske.

## Anwendungsszenarien

- **Adapterbasierte Datenkonvertierung:** In Systemen, die über Adapter mit ALI‑ und AB‑Schnittstellen verbunden sind, kann ALI_TO_AB als Brücke zwischen einem LINT‑liefernden und einem BYTE‑empfangenden Modul eingesetzt werden.
- **Reduzierung der Datenbreite:** Wenn ein 64‑Bit‑Wert (z. B. ein Zählerstand) auf ein 8‑Bit‑Signal abgebildet werden soll (z. B. ein einfacher Status‑BYTE), ist dieser Baustein geeignet.
- **Protokollumsetzung:** In heterogenen Steuerungssystemen, in denen unterschiedliche Adaptertypen verwendet werden, ermöglicht ALI_TO_AB eine einfache Typumwandlung.

## Vergleich mit ähnlichen Bausteinen

- **ALI_TO_Ax (LINT nach ANY):** Ein allgemeinerer Konverter, der LINT in einen beliebigen anderen Datentyp umwandelt. ALI_TO_AB ist auf BYTE spezialisiert und dadurch einfacher und direkter.
- **F_LINT_TO_BYTE:** Der zugrunde liegende IEC 61131‑Baustein. ALI_TO_AB kapselt diesen in eine adapterbasierte Schnittstelle, sodass er in Umgebungen verwendet werden kann, die nur Adapterkommunikation unterstützen.
- **Direkte Adapterverbindung:** Ohne Konvertierung könnte ein ALI-Adapter nicht direkt mit einem AB-Adapter verbunden werden. ALI_TO_AB schließt diese Lücke.

## Fazit

**ALI_TO_AB** ist ein einfacher, aber nützlicher Konvertierungsbaustein für die adapterbasierte Kommunikation. Er ermöglicht die Umwandlung eines LINT‑Werts in einen BYTE‑Wert unter Verwendung eines standardisierten IEC 61131‑Bausteins. Durch die vollständige Kapselung in zwei unidirektionale Adapter lässt er sich nahtlos in Adapter‑Netzwerke integrieren, ohne dass der Anwender die interne Typumwandlung selbst implementieren muss. Der Werteverlust durch die reduzierte Datenbreite ist bei der Verwendung zu beachten.