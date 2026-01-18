# NetEv2NetEv

```{index} single: NetEv2NetEv
```

<img width="1476" height="216" alt="image" src="https://github.com/user-attachments/assets/9bc9ef5f-0a9d-4bd3-8f83-d60a1665ff9c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `NetEv2NetEv` dient der Manipulation von Netzwerkereignissen (NetEv) innerhalb eines ISOBUS-basierten Systems. Sein primärer Zweck ist es, einen eingehenden Netzwerkereignis-Datensatz zu übernehmen und einen spezifischen Wert – den Netzwerk-Member-Handle – zu überschreiben. Der Block fungiert somit als einfacher Konverter oder Adapter für ISONETEVENT_T-Datenstrukturen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis löst die Verarbeitung des Funktionsblocks aus. Es ist mit den Daten-Eingängen `IN` und `s16Handle` verknüpft.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis signalisiert den Abschluss der Verarbeitung. Es wird nach der Bearbeitung des `REQ`-Ereignisses ausgelöst und ist mit dem (leeren) Daten-Ausgang verknüpft, der die manipulierte `ISONETEVENT_T`-Struktur ausgibt.

### **Daten-Eingänge**
*   **IN** (`isobus::pgn::ISONETEVENT_T`): Der Eingang für die ursprüngliche Netzwerkereignis-Datenstruktur, die manipuliert werden soll.
*   **s16Handle** (`INT`): Der neue Netzwerk-Member-Handle, der in die übergebene `ISONETEVENT_T`-Struktur geschrieben werden soll. Dieser Wert identifiziert den Controller/Function (CF) oder Benutzer, der als Quelle des Ereignisses dient.

### **Daten-Ausgänge**
*   **`<leer>`** (`isobus::pgn::ISONETEVENT_T`): Der Ausgang liefert die manipulierte `ISONETEVENT_T`-Datenstruktur. Der Name des Ausgangs ist leer, der Datentyp ist identisch mit dem des Eingangs `IN`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Die Funktionsweise des `NetEv2NetEv`-Blocks ist deterministisch und einfach:
1.  Bei Eintreffen eines `REQ`-Ereignisses wird die Funktion ausgeführt.
2.  Der gesamte Inhalt der Eingangsdatenstruktur `IN` wird in die Ausgangsdatenstruktur kopiert.
3.  Anschließend wird das Feld `.s16Handle` innerhalb dieser kopierten Ausgangsstruktur mit dem Wert des Eingangs `s16Handle` überschrieben.
4.  Das `CNF`-Ereignis wird ausgelöst, um die Bereitstellung des manipulierten Datensatzes am Ausgang zu signalisieren.

Der Block ändert nur das spezifizierte Handle-Feld. Alle anderen Felder der `ISONETEVENT_T`-Struktur bleiben unverändert.

## Technische Besonderheiten
*   **Datentyp**: Der Block arbeitet spezifisch mit dem Datentyp `isobus::pgn::ISONETEVENT_T`. Die genaue Struktur dieses Typs ist in der zugrundeliegenden `isobus::pgn`-Bibliothek definiert.
*   **Direkte Zuweisung**: Die Implementierung erfolgt über eine direkte Zuweisung in Structured Text (ST). Es findet keine zusätzliche Logik, Prüfung oder Fehlerbehandlung statt.
*   **Namenskonvention**: Der Daten-Ausgang besitzt keinen expliziten Namen, was in 4diac zulässig ist. Er wird über das `CNF`-Ereignis referenziert.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand oder Speicher. Sein Verhalten ist rein kombinatorisch: Bei jedem `REQ`-Ereignis wird sofort die beschriebene Operation durchgeführt und ein `CNF`-Ereignis generiert.

## Anwendungsszenarien
*   **Handle-Überschreibung in Event-Streams**: In Netzwerken, wo Ereignisse zwischen verschiedenen Controllern (CFs) weitergeleitet werden, muss der Quell-Handle (`s16Handle`) eventuell angepasst werden, um den aktuellen Absender korrekt zu identifizieren.
*   **Event-Proxy/Adapter**: Der Block kann als einfacher Proxy eingesetzt werden, um eingehende Netzwerkereignisse mit einer neuen Quellkennung zu versehen, bevor sie an nachgelagerte Verarbeitungslogik weitergegeben werden.
*   **Test und Simulation**: Zum Simulieren von Netzwerkereignissen von verschiedenen virtuellen Quellen (CFs) innerhalb eines Test-Setups.

## Vergleich mit ähnlichen Bausteinen
*   **E_SR (SR-Flip-Flop) oder E_D_FF (D-Flip-Flop)**: Diese Blöcke besitzen einen internen Zustand (Speicher). `NetEv2NetEv` ist zustandslos und manipuliert nur durchlaufende Daten.
*   **E_SELECT / E_MUX**: Diese Blöchte wählen zwischen verschiedenen Datenquellen aus oder leiten sie durch. `NetEv2NetEv` verändert aktiv einen Teil der durchlaufenden Daten.
*   **E_R_TRIG / E_F_TRIG**: Diese sind reine Ereignis-Trigger ohne Datenmanipulation. `NetEv2NetEv` ist ein datenverarbeitender Block.
*   **Generische ASSIGN-Bausteine**: Ein einfacher `ASSIGN`-Block kopiert einen Eingangswert 1:1 auf den Ausgang. `NetEv2NetEv` ist ein spezialisierter `ASSIGN`-Block für den Typ `ISONETEVENT_T`, der eine gezielte Modifikation (Handle-Überschreibung) vornimmt.

## Fazit
Der `NetEv2NetEv`-Funktionsblock ist ein spezialisiertes, schlankes Werkzeug für ISOBUS-Anwendungen. Er erfüllt eine klare und notwendige Nischenaufgabe: das Überschreiben des Quell-Handles in Netzwerkereignis-Datensätzen. Seine einfache, zustandslose Implementierung macht ihn robust und vorhersehbar. Für Entwickler, die mit ISOBUS PGNs und Netzwerkereignissen arbeiten, stellt er ein nützliches Hilfselement dar, um Datenflüsse korrekt zu kennzeichnen und anzupassen.
