# AI_SPLIT_8


![AI_SPLIT_8](./AI_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_SPLIT_8** dient dazu, ein analoges Eingangssignal (Typ *AI*) auf acht identische analoge Ausgangssignale zu verteilen. Der Baustein ist als generischer FB (GenericClassName: `GEN_AI_SPLIT`) implementiert und wird in der 4diac-IDE verwendet, um ein einzelnes analoges Signal mehrfach nutzbar zu machen.

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

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| **IN** | `adapter::types::unidirectional::AI` | Socket (Eingang) | Empfängt das analoge Signal, das auf alle Ausgänge verteilt wird. |
| **OUT1** – **OUT8** | `adapter::types::unidirectional::AI` | Plug (Ausgang) | Acht identische Ausgänge, die das am Eingang anliegende Signal bereitstellen. |

## Funktionsweise
Der FB besitzt keine eigene Verarbeitungslogik (keine Zustandsmaschine, kein ECC). Das am Adapter-Socket **IN** anliegende analoge Signal wird direkt und ohne Verzögerung an alle acht Adapter-Plugs (**OUT1** bis **OUT8**) weitergegeben. Es findet keine Signalumformung oder -verstärkung statt – das Signal wird eins zu eins dupliziert.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB ist als generischer Typ (`GEN_AI_SPLIT`) deklariert und kann daher zur Laufzeit mit einem konkreten analogen Datentyp parametrisiert werden.
- **Unidirektionale Adapter:** Alle verwendeten Adapter sind unidirektional, d.h. der Datenfluss verläuft ausschließlich vom Socket zu den Plugs.
- **Keine Ereignissteuerung:** Die Verteilung erfolgt ereignislos; ein anliegendes Signal wird sofort an alle Ausgänge weitergeleitet.

## Zustandsübersicht
Der FB besitzt keine interne Zustandsmaschine (ECC). Es gibt keine definierten Zustände – der Baustein arbeitet kontinuierlich und ohne eigenes Verhalten.

## Anwendungsszenarien
- **Signalverteilung:** Ein analoges Sensorsignal (z.B. Temperatur, Druck) soll an mehrere Steuerungsmodule oder Überwachungseinheiten gleichzeitig gesendet werden.
- **Redundanz:** Mehrere parallele Auswertungen desselben Signals in unterschiedlichen Teilen einer Anlage.
- **Prototyping:** Schnelles Bereitstellen eines Signals für mehrere Testpunkte in einer Entwicklungs- oder Simulationsumgebung.

## Vergleich mit ähnlichen Bausteinen
- **AI_SPLIT_2, AI_SPLIT_4:** Diese Bausteine verteilen ein analoges Signal auf zwei bzw. vier Ausgänge. Der vorliegende FB bietet mit acht Ausgängen eine höhere Anzahl paralleler Verbindungen.
- **DIO_SPLIT (digital):** Ein ähnlicher Splitter für digitale Signale, jedoch auf Basis von *DI/DO*-Adaptertypen. Der AI_SPLIT_8 ist spezifisch für analoge Signale ausgelegt.

## Fazit
Der **AI_SPLIT_8** ist ein einfacher, generischer Funktionsblock zur Vervielfachung eines analogen Signals. Seine klare Struktur – ein Eingang, acht Ausgänge, keine Ereignisse – macht ihn ideal für die unkomplizierte Signalverteilung in Automatisierungsanwendungen. Der generische Charakter erlaubt eine flexible Anpassung an verschiedene analoge Datentypen.