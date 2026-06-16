# AUS_TO_AR


![AUS_TO_AR](./AUS_TO_AR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUS_TO_AR** ist ein Composite FB zur Umwandlung eines AUS-Adapter-Interfaces (basierend auf USINT) in ein AR-Adapter-Interface (basierend auf REAL). Laut Beschreibung dient er zur Konvertierung zwischen diesen beiden Adaptertypen. Die aktuelle Implementierung (Version 1.0) leitet Ereignis- und Datenwerte lediglich durch, ohne eine explizite Umrechnung vorzunehmen – die eigentliche Typwandlung muss entweder durch die Adapter-Definitionen selbst oder durch nachträgliche Erweiterungen realisiert werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge vorhanden. Ereignisse werden ausschließlich über den **AUS_IN** Adapter übertragen.

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge vorhanden. Ereignisse werden ausschließlich über den **AR_OUT** Adapter ausgegeben.

### **Daten-Eingänge**
Keine separaten Daten-Eingänge vorhanden. Daten werden ausschließlich über den **AUS_IN** Adapter übertragen.

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge vorhanden. Daten werden ausschließlich über den **AR_OUT** Adapter ausgegeben.

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|---|---|---|---|
| `adapter::types::unidirectional::AUS` | AUS_IN | Socket (Eingang) | USINT-basierter Adapter-Eingang |
| `adapter::types::unidirectional::AR` | AR_OUT | Plug (Ausgang) | REAL-basierter Adapter-Ausgang |

## Funktionsweise
Der Baustein verbindet die Ereignis- und Datenkanäle des AUS_IN-Adapters direkt mit denen des AR_OUT-Adapters:

- **Ereignisdurchleitung**: Das am Socket `AUS_IN.E1` ankommende Ereignis wird unverzögert an den Plug `AR_OUT.E1` weitergeleitet.
- **Datendurchleitung**: Der vom Socket `AUS_IN.D1` bereitgestellte Datenwert (Typ USINT) wird direkt an `AR_OUT.D1` (Typ REAL) übergeben.

Da keine Typkonvertierung oder sonstige Verarbeitung im Netzwerk abgebildet ist, erfolgt die Umwandlung von USINT nach REAL entweder implizit durch die verwendete 4diac-Laufzeitumgebung oder muss durch Hinzufügen eines Konvertierungsbausteins (z. B. `CONV`) innerhalb einer Erweiterung des Composite-FBs realisiert werden.

## Technische Besonderheiten
- **Composite ohne innere Logik**: Das FBNetzwerk besteht ausschließlich aus zwei direkten Verbindungen; es sind keine weiteren Funktionsblöcke oder Zustandsautomaten enthalten.
- **Adapterbasierte Schnittstelle**: Statt einzelner Ereignis-/Dateneingänge und -ausgänge wird die gesamte Kommunikation über standardisierte unidirektionale Adapter abgewickelt. Dies erleichtert die Wiederverwendung in modularen Adapter-Hierarchien.
- **Unvollständige Implementierung**: Der Name und der Kommentar des Bausteins suggerieren eine aktive Konvertierung, die in der vorliegenden Version (1.0) jedoch nicht umgesetzt ist. Dies kann zu Laufzeitfehlern führen, wenn die Laufzeitumgebung keine implizite Typumwandlung unterstützt.

## Zustandsübersicht
Der Baustein besitzt keine Zustandsautomaten (ECC). Sein Verhalten ist rein kombinatorisch und auf die sofortige Durchleitung von Ereignissen und Daten beschränkt.

## Anwendungsszenarien
- **Ersatz für ältere Systeme**: Ein bestehendes AUS-Adapter-Interface (USINT) muss an eine Komponente angeschlossen werden, die ein AR-Adapter-Interface (REAL) erwartet.
- **Platzhalter in der Entwicklungsphase**: Der FB dient als vorläufige Verbindung, bis eine eigentliche Konvertierungslogik implementiert wird.
- **Testumgebungen**: Schnelle Kopplung zweier Adaptertypen ohne Datenänderung für Simulationen oder Tests.

## Vergleich mit ähnlichen Bausteinen
Typische Konvertierungsbausteine (z. B. `CONV` aus der Standardbibliothek) führen eine explizite Wertumrechnung mittels arithmetischer oder logischer Operationen durch. `AUS_TO_AR` hingegen delegiert die Umwandlung an die Adapterebene und übernimmt selbst keine Transformation. Es handelt sich eher um eine **strukturelle Anpassung** als um einen echten Konverter.

## Fazit
Der Funktionsblock `AUS_TO_AR` ist ein einfacher Adapter-zu-Adapter-Through-Pass-Baustein. Seine Nützlichkeit hängt stark davon ab, ob das Zielsystem automatische Typkonvertierungen zwischen USINT und REAL unterstützt. Ist dies nicht der Fall, muss der FB um eine explizite Konvertierungslogik erweitert werden. Er eignet sich daher als temporäre Lösung oder als Grundgerüst für eine vollständige Implementierung.