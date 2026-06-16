# AR_TO_AD


![AR_TO_AD](./AR_TO_AD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AR_TO_AD` dient als zusammengesetzter Baustein (Composite FB) zur Umwandlung eines REAL-Wertes, der über einen unidirektionalen AR-Adapter hereinkommt, in einen DWORD-Wert, der über einen unidirektionalen AD-Adapter ausgegeben wird. Die Konvertierung erfolgt nach IEC 61131-3 mittels des Bausteins `F_REAL_TO_DWORD`. Der FB kapselt die notwendigen Ereignis- und Datenverbindungen und erlaubt eine einfache Integration in bestehende Adapter-basierte Kommunikationsstrukturen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Eingang | Typ | Beschreibung |
|---------|-----|--------------|
| `AR_IN.E1` | Adapter-Ereignis | Empfängt das Auslöseereignis vom AR-Adapter, welches die Konvertierung startet. |

### **Ereignis-Ausgänge**

| Ausgang | Typ | Beschreibung |
|---------|-----|--------------|
| `AD_OUT.E1` | Adapter-Ereignis | Sendet ein Ereignis an den AD-Adapter, sobald der konvertierte DWORD-Wert anliegt. |

### **Daten-Eingänge**

| Eingang | Typ | Beschreibung |
|---------|-----|--------------|
| `AR_IN.D1` | REAL | Der zu konvertierende REAL-Wert, der vom AR-Adapter bereitgestellt wird. |

### **Daten-Ausgänge**

| Ausgang | Typ | Beschreibung |
|---------|-----|--------------|
| `AD_OUT.D1` | DWORD | Der konvertierte DWORD-Wert, der an den AD-Adapter übergeben wird. |

### **Adapter**
Der FB besitzt einen **Socket** vom Typ `adapter::types::unidirectional::AR` (mit der Bezeichnung `AR_IN`) und einen **Plug** vom Typ `adapter::types::unidirectional::AD` (mit der Bezeichnung `AD_OUT`). Die tatsächlichen Ein- und Ausgangssignale sind über die Ereignis- und Daten-Pins dieser Adapter zugänglich.

## Funktionsweise
1. Der FB wartet auf ein Ereignis am Ereignis-Eingang `AR_IN.E1`.
2. Gleichzeitig wird der aktuelle Wert am Daten-Eingang `AR_IN.D1` (REAL) übernommen.
3. Intern wird der Baustein `F_REAL_TO_DWORD` (aus der IEC 61131-3-Bibliothek) aufgerufen, der die Umwandlung vornimmt.
4. Nach erfolgreicher Konvertierung wird der resultierende DWORD-Wert an den Daten-Ausgang `AD_OUT.D1` gelegt.
5. Anschließend wird ein Ereignis am Ausgang `AD_OUT.E1` ausgegeben, um den angeschlossenen AD-Adapter zu benachrichtigen.

Der gesamte Vorgang erfolgt synchron in einem Schritt, d.h. der FB ist rein ereignisgesteuert und führt keine internen Zustände.

## Technische Besonderheiten
- **Composite FB:** Die Logik wird ausschließlich durch die Verknüpfung des internen `F_REAL_TO_DWORD`-Bausteins realisiert. Es gibt keine eigene Zustandsmaschine oder komplexe Algorithmen.
- **Adapter-Kopplung:** Der FB kapselt die Konvertierung auf Adapterebene, sodass er ohne zusätzliche Anpassungen in Adapter-basierte Architekturen (z.B. verteilte Systeme mit 4diac) eingefügt werden kann.
- **IEC 61131-3 Konformität:** Die eigentliche Umwandlung erfolgt durch einen genormten Baustein, was die Portabilität und Standardkonformität erhöht.
- **Paketname:** Der Baustein wird unter dem Paket `adapter::conversion::unidirectional` bereitgestellt und importiert `iec61131::conversion::F_REAL_TO_DWORD`.

## Zustandsübersicht
Da es sich um einen kombinatorischen Composite-FB handelt, besitzt der Baustein keinen internen Zustandsautomaten. Die Funktionalität ist rein ereignisgesteuert und wird bei jedem Ereignis am Eingang einmalig durchlaufen.

## Anwendungsszenarien
- **Datenprotokoll-Adaption:** Wenn ein REAL-Wert (z.B. ein Messwert) über ein Bussystem nur als DWORD (z.B. bei vielen Feldbusprotokollen) übertragen werden kann.
- **Adapterbrücke:** In Systemen, die sowohl REAL- als auch DWORD-Adapter verwenden, kann dieser FB als einfache Umwandlungseinheit zwischen zwei Adaptertypen dienen.
- **Wiederverwendbare Konvertierung:** Durch die Kapselung kann die Konvertierung mehrfach in verschiedenen Netzwerken eingesetzt werden, ohne dass jedes Mal die Verbindungen manuell hergestellt werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **F_REAL_TO_DWORD:** Der direkte Baustein aus IEC 61131-3 bietet dieselbe Konvertierung, erfordert jedoch manuelle Verdrahtung von Ereignis- und Datenleitungen. `AR_TO_AD` kapselt dies in einer Adapter-Schnittstelle, was die Integration in Adapter-Netzwerke vereinfacht.
- **AR_TO_SINT / AR_TO_INT:** Vergleichbare Konvertierungen existieren für andere ganzzahlige Datentypen, jedoch nicht als Adapter-Version. `AR_TO_AD` ist speziell für DWORD und Adapter konzipiert.
- **Selbstdefinierte Composite-FBs:** Prinzipiell könnte jeder Anwender eine ähnliche Kapselung erstellen. Der Baustein bietet jedoch eine standardisierte Lösung mit klarer Paketstruktur.

## Fazit
Der `AR_TO_AD`-Funktionsblock ist ein spezialisierter Composite-Baustein, der die Umwandlung eines REAL- auf einen DWORD-Wert auf Adapterebene ermöglicht. Er zeichnet sich durch seine einfache Handhabung, Standardkonformität und die nahtlose Integration in unidirektionale Adapter-Kommunikationen aus. Durch die Verwendung des bewährten IEC 61131-3-Bausteins `F_REAL_TO_DWORD` wird eine zuverlässige und portable Konvertierung gewährleistet.