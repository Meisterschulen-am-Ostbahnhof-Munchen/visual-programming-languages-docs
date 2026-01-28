# CallbackFB

```{index} single: CallbackFB
```

<img width="1298" height="232" alt="image" src="https://github.com/user-attachments/assets/3e1dbee0-183b-4d4f-a9e7-110505249cb4" />

* * * * * * * * * *
## Einleitung
Der `CallbackFB` ist ein Composite-Funktionsblock, der die Verwendung des Callback-Mechanismus in Subapplikationen vereinfacht. Er dient als Wrapper-Baustein, um eine standardisierte Schnittstelle für die asynchrone Kommunikation über einen Callback-Adapter bereitzustellen. Sein primärer Zweck ist die Entkopplung und strukturierte Handhabung von Bestätigungsnachrichten (`CNF`) und Anfragen (`REQ`) innerhalb eines Funktionsblocknetzwerks.

![CallbackFB](CallbackFB.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **`CNF`**: Bestätigungsereignis (Confirmation). Dieses Ereignis wird vom angeschlossenen Plug empfangen und signalisiert den Abschluss einer Anfrage oder das Eintreffen von Daten.

### **Ereignis-Ausgänge**
*   **`REQ`**: Anfrageereignis (Request). Dieses Ereignis wird vom internen Socket des Adapters ausgelöst und signalisiert eine ausstehende Aktion oder Datenanforderung.

### **Daten-Eingänge**
*   **`DI1`**: Dateneingang vom Typ `isobus::pgn::CAN_MSG`. Dieser Eingang transportiert die CAN-Nachrichtendaten, die mit dem eingehenden `CNF`-Ereignis assoziiert sind.

### **Daten-Ausgänge**
*   *(Keine direkten Datenausgänge am FB definiert. Die Daten werden über den Adapter weitergeleitet.)*

### **Adapter**
*   **`PLUG1`**: Ein Plug-Adapter vom Typ `isobus::pgn::tx::Callback`. Dieser Adapter stellt die Verbindung zu einem entsprechenden Socket-Adapter in einem anderen Funktionsblock her und realisiert das Callback-Muster.

## Funktionsweise
Der `CallbackFB` fungiert als transparente Vermittlungsinstanz. Sein internes Netzwerk (FBNetwork) verbindet die öffentlichen Schnittstellen des Composite-FB direkt mit den Pins des integrierten `Callback`-Adapters (`PLUG1`).
1.  Ein eingehendes `CNF`-Ereignis wird direkt an den `CNF`-Eingang des `PLUG1`-Adapters weitergeleitet.
2.  Die mit `CNF` verbundenen Daten (`DI1` vom Typ `isobus::pgn::CAN_MSG`) werden parallel an den Dateneingang `DO1` des `PLUG1`-Adapters übergeben.
3.  Wenn der interne Socket des `PLUG1`-Adapters ein `REQ`-Ereignis auslöst, wird dieses direkt an den öffentlichen `REQ`-Ereignisausgang des `CallbackFB` weitergeleitet.

Der Baustein selbst führt keine zusätzliche Logik oder Datenverarbeitung durch. Seine Funktion besteht ausschließlich in der strukturierten Bündelung und Durchreichung von Ereignissen und Daten.

## Technische Besonderheiten
*   **Typisierung**: Der Dateneingang `DI1` verwendet den spezifischen Datentyp `isobus::pgn::CAN_MSG`, was auf eine Anwendung im Kontext von ISOBUS- und CAN-basierten Agrarsystemen hindeutet.
*   **Adapter-Pattern**: Die gesamte Funktionalität basiert auf dem 61499-Adapterkonzept. Der FB kapselt einen `Plug` und benötigt für den Betrieb einen korrespondierenden `Socket` des Typs `isobus::pgn::tx::Callback` in einem anderen Baustein.
*   **Transparenz**: Als Composite-FB ohne zusätzliche Algorithmen ist sein Verhalten vollständig durch das interne Verbindungsnetzwerk definiert und somit vorhersagbar.

## Zustandsübersicht
Da es sich um einen rein durchschleifenden Composite-Baustein ohne interne Zustandsmaschine (Basic FB) oder zyklisches Verhalten (Service Interface FB) handelt, besitzt der `CallbackFB` keinen eigenen Zustandsautomaten. Sein "Zustand" wird durch den Zustand des verbundenen Adapter-Paares (`PLUG1` und sein korrespondierender Socket) bestimmt.

## Anwendungsszenarien
*   **Strukturierung von Subapplikationen**: In komplexen Subapplikationen kann der `CallbackFB` verwendet werden, um eine saubere und wiederverwendbare Schnittstelle für Callback-Kommunikation bereitzustellen.
*   **Entkopplung von Komponenten**: Er ermöglicht die lose Kopplung zwischen einem Dienst-Anbieter (der den Socket bereitstellt) und einem Dienst-Nutzer (der diesen FB einsetzt), was die Wartbarkeit und Testbarkeit erhöht.
*   **ISOBUS-Kommunikation**: Spezifische Anwendung in Steuerungssystemen für landwirtschaftliche Maschinen, um die Übertragung von CAN-Nachrichten (PGNs) asynchron zu bestätigen oder anzufordern.

## Vergleich mit ähnlichen Bausteinen
*   **Direkte Adapterverbindung**: Anstatt einen `Callback`-Adapter direkt in ein Netzwerk einzubinden, bietet der `CallbackFB` eine gebündelte, benannte Schnittstelle (`CNF`/`REQ`/`DI1`), die in manchen Entwürfen lesbarer sein kann.
*   **Einfache E_CLASS vs. CallbackFB**: Ein einfacher E_CLASS-Baustein (Event Splitter/Merger) könnte ähnliche Ereigniswegleitungen durchführen, jedoch nicht die typsichere Datenverbindung für `isobus::pgn::CAN_MSG` zusammen mit dem standardisierten Adapter-Interface bereitstellen.
*   **Generische Wrapper-FBs**: Im Gegensatz zu generischen Wrapper-Bausteinen ist der `CallbackFB` auf einen spezifischen Datentyp und Adapter spezialisiert, was Typsicherheit und klare Semantik gewährleistet.

## Fazit
Der `CallbackFB` ist ein nützliches Hilfskonstrukt für die strukturierte Anwendung des Adapter-Patterns in IEC 61499, speziell im ISOBUS-Umfeld. Er reduziert die Komplexität im Hauptnetzwerk, indem er die Verbindungslogik für Callback-Kommunikation in einen einzigen, wiederverwendbaren Composite-Baustein auslagert. Seine Stärke liegt in der Einfachheit und Klarheit, während er selbst keine aktive Logik implementiert. Er ist die ideale Wahl, wenn eine standardisierte und typsichere Callback-Schnittstelle in einer Subapplikation benötigt wird.