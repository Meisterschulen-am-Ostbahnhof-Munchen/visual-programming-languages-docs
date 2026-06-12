# ASSEMBLE_AD_FROM_AB


![ASSEMBLE_AD_FROM_AB](./ASSEMBLE_AD_FROM_AB.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **ASSEMBLE_AD_FROM_AB** dient dazu, vier einzelne Byte-Werte, die über unidirektionale **AB**-Adapter (Byte) hereinkommen, zu einem 32‑Bit **DWORD**-Wert zusammenzufügen und über einen unidirektionalen **AD**-Adapter auszugeben. Die Kombination der Bytes erfolgt in der Reihenfolge BYTE_00 (niederwertigstes Byte) bis BYTE_03 (höchstwertiges Byte). Der Baustein verwendet dazu einen internen Zusammenfüger und einen flankengesteuerten Flip‑Flop, um die Ausgabe erst nach vollständigem Abschluss der Zusammenführung zu aktualisieren.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereignis-Eingänge. Ereignisse werden über die angeschlossenen **Socket-Adapter** (BYTE_00 … BYTE_03) empfangen.

### **Ereignis-Ausgänge**
Es gibt keinen direkten Ereignis-Ausgang. Das Ausgangsereignis wird über den **Plug-Adapter** (OUT) bereitgestellt.

### **Daten-Eingänge**
Es gibt keine direkten Daten-Eingänge. Alle Daten werden über die **Socket-Adapter** (BYTE_00 … BYTE_03) entgegengenommen.

### **Daten-Ausgänge**
Es gibt keinen direkten Daten-Ausgang. Der zusammengeführte DWORD‑Wert wird über den **Plug-Adapter** (OUT) ausgegeben.

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| BYTE_00 | `adapter::types::unidirectional::AB` | Socket | Byte 0 (niederwertigstes Byte) |
| BYTE_01 | `adapter::types::unidirectional::AB` | Socket | Byte 1 |
| BYTE_02 | `adapter::types::unidirectional::AB` | Socket | Byte 2 |
| BYTE_03 | `adapter::types::unidirectional::AB` | Socket | Byte 3 (höchstwertiges Byte) |
| OUT | `adapter::types::unidirectional::AD` | Plug | 32‑Bit DWORD‑Ausgang |

## Funktionsweise
Der Baustein arbeitet vollständig im Inneren eines Subapplikationsnetzwerks:

1. Ein Ereignis an einem der vier Socket‑Adapter (BYTE_00 … BYTE_03) löst über die jeweilige `E1`‑Leitung den **REQ**‑Eingang des internen `ASSEMBLE_DWORD_FROM_BYTES`‑Bausteins aus.
2. Dieser Baustein liest die aktuellen Werte an seinen Daten‑Eingängen (`BYTE_00` … `BYTE_03`) ein, setzt sie zu einem 32‑Bit‑Wert zusammen und signalisiert dies mit **CNF**.
3. Das **CNF**‑Ereignis triggert den **CLK**‑Eingang des internen `E_D_FF_ANY`‑Flip‑Flops. Das Flip‑Flop übernimmt den am **D**‑Eingang anliegenden Datenwert (das zusammengefügte DWORD).
4. Der Ausgang **Q** des Flip‑Flops wird permanent auf den **D1**‑Datenausgang des Plug‑Adapters **OUT** gelegt.
5. Gleichzeitig wird mit dem Flip‑Flop‑Ausgangssignal das Ereignis **E1** des Plug‑Adapters ausgelöst, so dass die empfangende Seite über den neuen Wert informiert wird.

Auf diese Weise wird sichergestellt, dass der Ausgang nur dann aktualisiert wird, wenn ein Ereignis an mindestens einem Socket‑Adapter eingetroffen ist und die Zusammenführung abgeschlossen wurde. Der letzte zusammengeführte Wert bleibt solange erhalten, bis ein neuer Vorgang abgeschlossen ist.

## Technische Besonderheiten
- **Ereignissynchronisation**: Alle vier Socket‑Ereignisse werden auf einen gemeinsamen `REQ` des Zusammenführungsbausteins gelegt. Dadurch wird die Verarbeitung bei jedem eingehenden Byte‑Ereignis neu angestoßen – es ist nicht notwendig, dass alle vier Bytes gleichzeitig aktualisiert werden.
- **Zwischenspeicherung**: Der eingebaute `E_D_FF_ANY` verhindert eine Ausgabe während der Zusammenführungsphase. Erst wenn das Ergebnis stabil vorliegt, wird es an den Plug weitergegeben.
- **Adapter‑basiert**: Der Baustein besitzt keine direkten Ein‑/Ausgänge, sondern kommuniziert ausschließlich über standardisierte unidirektionale Adapter (`AB` und `AD`). Dies erlaubt eine flexible Einbindung in existierende Adapter‑Schnittstellen.

## Zustandsübersicht
Der Baustein selbst besitzt keinen expliziten Zustandsautomaten. Das Verhalten wird durch die internen Bausteine bestimmt:
- **Warten auf Ereignis**: Es liegt kein neues Ereignis an den Sockets an. Der Ausgangswert ist statisch.
- **Summieren & Aktualisieren**: Ein Ereignis trifft ein → Zusammenführung wird ausgelöst → Flip‑Flop übernimmt neuen Wert → Ausgang wird aktualisiert.
- **Warten auf nächstes Ereignis**: Nach erfolgter Aktualisierung bleibt der Zustand bis zum nächsten Socket‑Ereignis erhalten.

## Anwendungsszenarien
- **Datenstromvereinigung**: Zusammenführen von vier Byte‑orientierten Sensor‑ oder Kommunikationsdaten zu einem 32‑Bit‑Wert (z. B. für eine Feldbus‑Schnittstelle).
- **Protokoll‑Wrapper**: Kombination von einzelnen Bytes aus unterschiedlichen Quellen zu einem vollständigen Datenwort, das anschließend über einen AD‑Adapter an eine übergeordnete Logik weitergegeben wird.
- **Test‑ und Simulationsumgebungen**: Einsatz als Konverter zwischen bestehenden Byte‑Adapter‑Komponenten und DWORD‑Adapter‑Komponenten.

## Vergleich mit ähnlichen Bausteinen
- **Direkter Datentyp‑Konverter** (z. B. `BYTE_TO_DWORD`): Diese arbeiten oft mit einfachen Daten‑Ein‑/Ausgängen ohne Ereignisprotokoll. Der `ASSEMBLE_AD_FROM_AB` hingegen integriert die Ereignissteuerung und ist auf die Adapter‑Schnittstelle zugeschnitten.
- **Manuelle Verkettung von Adaptern**: Statt vier separaten `AB`‑Adaptern und einem manuell aufgebauten Netzwerk bietet dieser Baustein eine vorgefertigte und getestete Lösung, die weniger Verdrahtungsaufwand erfordert.

## Fazit
Der **ASSEMBLE_AD_FROM_AB** ist ein spezialisierter, adapter‑basierter Funktionsblock zur Zusammenführung von vier Byte‑Werten zu einem DWORD. Durch die interne Verwendung eines Zusammenfügers und eines Flip‑Flops wird eine zuverlässige, ereignisgesteuerte Aktualisierung des Ausgangswerts erreicht. Er eignet sich ideal für Systeme, die auf standardisierten unidirektionalen Adaptern aufbauen und eine saubere, flackerschutzfreie Datenweitergabe benötigen.