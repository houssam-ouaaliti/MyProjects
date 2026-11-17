package blazing.jeux.entity;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class CardTest {

    @Test
    void nouvelleCard_discardFalseParDefaut() {
        Card card = new Card();
        assertFalse(card.isDiscard());
    }

    @Test
    void nouvelleCard_holderNullParDefaut() {
        Card card = new Card();
        assertNull(card.getHolder());
    }

    @Test
    void setColorEtValue_retournentCorrectement() {
        Card card = new Card();
        card.setColor("ROUGE");
        card.setValue("7");
        assertEquals("ROUGE", card.getColor());
        assertEquals("7", card.getValue());
    }

    @Test
    void setDiscard_true_carteEstSurDefausse() {
        Card card = new Card();
        card.setDiscard(true);
        assertTrue(card.isDiscard());
    }

    @Test
    void setHolder_lieBienLeGamePlayer() {
        Card card = new Card();
        GamePlayer gp = new GamePlayer();
        card.setHolder(gp);
        assertEquals(gp, card.getHolder());
    }

    @Test
    void cardWild8_valeurEst8() {
        Card wild = new Card();
        wild.setValue("8");
        wild.setColor("ROUGE");
        assertEquals("8", wild.getValue());
        assertFalse(wild.isDiscard());
    }

    @Test
    void cardOscarsSwap_couleurNone() {
        Card swap = new Card();
        swap.setValue("OSCARS_SWAP");
        swap.setColor("NONE");
        assertEquals("OSCARS_SWAP", swap.getValue());
        assertEquals("NONE", swap.getColor());
    }

    @Test
    void cardDansMain_holderNonNull() {
        Card card = new Card();
        GamePlayer gp = new GamePlayer();
        card.setHolder(gp);
        assertNotNull(card.getHolder());
    }

    @Test
    void cardDansPioche_holderNullEtPasDefausse() {
        Card card = new Card();
        card.setColor("BLEU");
        card.setValue("3");
        // Dans la pioche : holder null, pas en défausse
        assertNull(card.getHolder());
        assertFalse(card.isDiscard());
    }
}