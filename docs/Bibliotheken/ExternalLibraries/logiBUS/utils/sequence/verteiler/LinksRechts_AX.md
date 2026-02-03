# LinksRechts_AX


![LinksRechts_AX](.././LinksRechts_AX.svg)

*Hinweis: Ein Bild des Funktionsbausteins ist hier nicht verfügbar.*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **LinksRechts_AX** (aus dem Paket `logiBUS::utils::sequence::verteiler`) dient der Steuerung eines alternierenden Prozesses mit zwei Richtungen (Rechtslauf und Linkslauf). Er wurde konzipiert, um zwischen zwei Ausgängen hin- und herzuschalten, wobei Pausenzustände berücksichtigt werden.

Besonders hervorzuheben ist die Möglichkeit, den automatischen Wechsel durch digitale Eingänge (`DI_Rechts`, `DI_Links`) zu unterbinden, um einen Lauf in nur einer Richtung zu erzwingen. Der Baustein nutzt hierfür die `AX` Adapter-Schnittstelle.

## Schnittstellenstruktur

Der Baustein verwendet primär Adapter für die Kommunikation, stellt jedoch auch einen Status-String als direkten Ausgang zur Verfügung.

### **Ereignis-Eingänge**
*Es sind keine direkten Ereignis-Eingänge vorhanden. Die Steuerung erfolgt über die Ereignisse der Adapter-Sockets.*

### **Ereignis-Ausgänge**
| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **EO** | Event | Ereignis, das ausgelöst wird, wenn sich der interne Zustand (`STATE`) ändert. |

### **Daten-Eingänge**
*Es sind keine direkten Daten-Eingänge vorhanden. Die Daten werden über die Adapter-Sockets eingelesen.*

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **STATE** | STRING | Aktueller Zustand des Bausteins (z.B. "Rechtslauf", "Linkslauf_Pause"). |

### **Adapter**

**Sockets (Eingangs-Schnittstellen):**
| Name | Typ | Kommentar |
| :--- | :--- | :--- |
| **EIN** | adapter::types::unidirectional::AX | **Einschalten**: Das Hauptsignal zum Starten und Stoppen der Bewegung. |
| **DI_Rechts** | adapter::types::unidirectional::AX | **Nur Rechtslauf**: Wenn aktiv, wird ein Wechsel auf Linkslauf verhindert und der Rechtslauf erzwungen. |
| **DI_Links** | adapter::types::unidirectional::AX | **Nur Linkslauf**: Wenn aktiv, wird ein Wechsel auf Rechtslauf verhindert und der Linkslauf erzwungen. |

**Plugs (Ausgangs-Schnittstellen):**
| Name | Typ | Kommentar |
| :--- | :--- | :--- |
| **Rechts** | adapter::types::unidirectional::AX | **Rechtslauf**: Ausgangssignal für die Rechtsbewegung. |
| **Links** | adapter::types::unidirectional::AX | **Linkslauf**: Ausgangssignal für die Linksbewegung. |

## Funktionsweise

Der **LinksRechts_AX** Baustein implementiert eine Zustandsmaschine, die grundsätzlich zwischen einer Rechts- und einer Linksbewegung alterniert, getrennt durch Pausenphasen.

1.  **Start:** Aus dem `START`-Zustand heraus entscheidet der Baustein basierend auf den Eingängen `EIN` und `DI_Links`, ob zuerst in den Linkslauf oder Rechtslauf geschaltet wird.
2.  **Aktivierung (Lauf):** Solange das Signal `EIN.D1` (Daten) zusammen mit einem Event `EIN.E1` als `TRUE` anliegt, geht der Baustein in einen aktiven Zustand (`Rechtslauf` oder `Linkslauf`). Dabei wird der entsprechende Ausgangsadapter (`Rechts` oder `Links`) auf `TRUE` gesetzt.
3.  **Deaktivierung (Pause):** Wird `EIN.D1` zu `FALSE` (Ausschalten), wechselt der Baustein in den entsprechenden Pausenzustand (`Rechtslauf_Pause` oder `Linkslauf_Pause`). Die Ausgänge werden deaktiviert (`FALSE`).
4.  **Wechsel-Logik (Alternieren):**
    *   Befindet sich der Baustein in `Rechtslauf_Pause` und wird wieder eingeschaltet (`EIN` = TRUE), wechselt er standardmäßig in den **Linkslauf**.
    *   Befindet sich der Baustein in `Linkslauf_Pause` und wird wieder eingeschaltet, wechselt er standardmäßig in den **Rechtslauf**.
5.  **Override-Logik (Erzwingen):**
    *   Ist im Zustand `Rechtslauf_Pause` der Eingang `DI_Rechts` aktiv, wird der Wechsel zum Linkslauf unterbunden und erneut der **Rechtslauf** gestartet.
    *   Ist im Zustand `Linkslauf_Pause` der Eingang `DI_Links` aktiv, wird der Wechsel zum Rechtslauf unterbunden und erneut der **Linkslauf** gestartet.

## Technische Besonderheiten

*   **AX-Adapter:** Der Baustein nutzt den generischen `unidirectional::AX` Typ. Dieser kombiniert typischerweise ein boolesches Datensignal (`D1`) mit einem Ereignis (`E1`).
*   **Priorisierung:** Laut der internen Beschreibung ist "Nur Rechtslauf vorrangig vor Nur Linkslauf", was sich in den Startbedingungen widerspiegelt, jedoch wird die Sequenzlogik primär durch den vorherigen Zustand (History) bestimmt.
*   **Status-Reporting:** Jede Zustandsänderung aktualisiert die `STATE`-Variable und feuert das `EO`-Event. Die Zustandsnamen werden über eine externe Enumeration (`STATES::...`) bezogen.

## Zustandsübersicht

Die ECC (Execution Control Chart) definiert folgende Zustände:

| Zustand Name | Aktion | Beschreibung |
| :--- | :--- | :--- |
| **START** | - | Initialzustand. Wartet auf das `EIN`-Signal. |
| **Rechtslauf** | `Set_Rechts_TRUE`, `Set_Links_FALSE`, Status update | Aktiviert den Adapter `Rechts`, deaktiviert `Links`. |
| **Rechtslauf_Pause** | `Set_Rechts_FALSE`, `Set_Links_FALSE`, Status update | Beide Ausgänge aus. System merkt sich, dass es zuletzt rechts war. |
| **Linkslauf** | `Set_Rechts_FALSE`, `Set_Links_TRUE`, Status update | Aktiviert den Adapter `Links`, deaktiviert `Rechts`. |
| **Linkslauf_Pause** | `Set_Rechts_FALSE`, `Set_Links_FALSE`, Status update | Beide Ausgänge aus. System merkt sich, dass es zuletzt links war. |

## Anwendungsszenarien

*   **Pendelbetrieb:** Automatische Steuerung von Mechanismen, die sich hin- und herbewegen müssen (z.B. ein Scheibenwischer-Modus oder ein Reinigungskopf), gesteuert durch einen einzigen Taster (`EIN`).
*   **Beregnungsanlagen:** Sequentielle Ansteuerung von zwei Sektoren (Sektor Rechts -> Pause -> Sektor Links -> Pause), wobei bei Bedarf ein Sektor mehrfach hintereinander aktiviert werden kann (mittels `DI_Rechts`/`DI_Links`).
*   **Reversiermotor:** Steuerung eines Motors, der bei jedem Neustart die Drehrichtung ändern soll, sofern nicht anders vorgegeben.

## ⚖️ Vergleich mit ähnlichen Bausteinen

*   **Einfaches Toggle (FlipFlop):** Ein Standard-Toggle schaltet nur einen Ausgang Ein/Aus. `LinksRechts_AX` schaltet zwischen *zwei* Ausgängen um.
*   **RS-Glied:** Ein RS-Glied speichert nur einen Zustand basierend auf Set/Reset. Dieser Baustein beinhaltet eine Sequenzlogik (History-Memory), da er weiß, welcher Zustand *vor* der Pause aktiv war.
*   **E_SELECT:** Ähnelt einem Selektor, aber `LinksRechts_AX` beinhaltet die zeitliche Komponente des "Pausierens" und des automatischen Wechsels beim nächsten Startsignal.

## Fazit

Der Funktionsbaustein **LinksRechts_AX** ist eine spezialisierte Komponente für Ablaufsteuerungen, die einen alternierenden Betrieb zwischen zwei Ausgängen erfordern. Durch die Integration der Adapter-Technologie (`AX`) und die Möglichkeit, die Sequenz durch digitale Eingänge (`DI`) zu beeinflussen, bietet er eine flexible Lösung für sequentielle Steuerungsaufgaben mit Richtungspriorisierung.